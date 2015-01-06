<?php

/**
 * Represents an OAI-PMH request.
 *
 * This class parses and performs error checks against the parameters of the
 * requested URL. The view plugin delegates those tasks to an object of this
 * class, and accesses its public members when needed instead of directly
 * checking the $_REQUEST.
 */
class views_oai_pmh_request {
  public $base_url = ''; // The base URL of this OAI-PMH request.
  public $verb = '';
  public $callback = ''; // Name of the style plugin callback corresponding to $verb.
  public $metadata_format; // A views_oai_pmh_metadata_format object.
  public $resumption_token = '';
  public $nid = 0;
  public $from = 0;
  public $until = 0;
  // TODO: Add $set if we decide to support sets.
  public $response_date = '';
  public $response_timestamp = 0;
  public $errors = array();

  // Arguments as given by the user. Do NOT use those unvalidated arguments
  // during request execution. These are only needed for the 'request' element
  // of the responses.
  public $original_args = array();

  /**
   * Constructs the object based on $_REQUEST data.
   */
  function __construct($base_url, $allowed_metadata_formats, $live_preview = FALSE) {
    $this->base_url = $base_url;

    if ($live_preview) {
      $args['verb'] = 'ListRecords';
      $args['metadataPrefix'] = 'oai_dc';
    }
    else {
      $args = $_REQUEST;
    }

    if (isset($args['q'])) {
      // Ignore the Drupal 'q' argument.
      unset($args['q']);
    }

    $this->response_timestamp = time();
    $this->response_date = gmstrftime('%Y-%m-%dT%H:%M:%SZ', $this->response_timestamp);

    if (!isset($args['verb'])) {
      $this->errors[] = new views_oai_pmh_error_missing_verb();
    }
    elseif (!in_array($args['verb'], array('GetRecord', 'ListIdentifiers', 'ListRecords', 'Identify', 'ListMetadataFormats', 'ListSets'))) {
      $this->errors[] = new views_oai_pmh_error_bad_verb();
    }
    else {
      $this->verb = $args['verb'];
      unset($args['verb']); // Remove this one before further parsing.

      switch ($this->verb) {
        case 'Identify':
          $this->callback = 'identify';
          $this->parse_arguments($args);
          break;

        case 'ListMetadataFormats':
          $this->callback = 'list_metadata_formats';
          $this->parse_arguments($args, array(), array('identifier'));
          break;

        case 'ListIdentifiers':
          $this->callback = 'list_identifiers';
          $this->parse_arguments($args, array('metadataPrefix'), array('resumptionToken', 'from', 'until', 'set'));
          $this->parse_metadata_prefix($args, $allowed_metadata_formats);
          break;

        case 'GetRecord':
          $this->callback = 'get_record';
          $this->parse_arguments($args, array('identifier', 'metadataPrefix'));
          $this->parse_metadata_prefix($args, $allowed_metadata_formats);
          break;

        case 'ListRecords':
          $this->callback = 'list_records';
          $this->parse_arguments($args, array('metadataPrefix'), array('resumptionToken', 'from', 'until', 'set'));
          $this->parse_metadata_prefix($args, $allowed_metadata_formats);
          break;

        case 'ListSets':
          $this->parse_arguments($args);
          $this->errors[] = new views_oai_pmh_error_no_set_hierarchy();
          break;
      }
    }
  }

  public function make_record_identifier_prefix() {
    $url_parts = parse_url($this->base_url);
    return 'oai:' . $url_parts['host'] . ':';
  }

  /**
   * Parse the given arguments, initializing each argument's corresponding
   * member variable if the argument is valid, or appending an error when it is
   * not.
   */
  protected function parse_arguments($args, $required = array(), $optional = array()) {
    $possible = array_merge($required, $optional);

    // Preserve original value of every authorized tag.
    foreach ($possible as $arg) {
      if (isset($args[$arg])) {
        $this->original_args[$arg] = $args[$arg];
      }
    }

    // Parse resumption token.
    if (isset($args['resumptionToken']) && in_array('resumptionToken', $possible)) {
      if (count($args) > 1) {
        $this->errors[] = new views_oai_pmh_error_exclusive_argument('resumptionToken');
      }
      else {
        $this->resumption_token = $args['resumptionToken'];
      }
      return; // No more arguments to check since resumptionToken is exclusive.
    }

    // Check required arguments.
    foreach ($required as $arg) {
      if (!isset($args[$arg])) {
        $this->errors[] = new views_oai_pmh_error_missing_argument($arg);
      }
    }

    // Check for extraneous arguments.
    foreach (array_keys($args) as $arg) {
      if (!in_array($arg, $possible)) {
        $this->errors[] = new views_oai_pmh_error_bad_argument($arg);
        unset($args[$arg]); // Prevent further error reports about the same argument.
      }
    }

    // Check for the 'set' argument (unsupported).
    if (isset($args['set'])) {
      $this->errors[] = new views_oai_pmh_error_no_set_hierarchy();
    }

    // Check date arguments.
    $from_granularity = 0;
    $until_granularity = 0;
    if (isset($args['from'])) {
      if (!$from_granularity = $this->check_date_format($args['from'])) {
        $this->errors[] = new views_oai_pmh_error_bad_value('from', $args['from']);
      }
    }
    if (isset($args['until'])) {
      if (!$until_granularity = $this->check_date_format($args['until'])) {
        $this->errors[] = new views_oai_pmh_error_bad_value('until', $args['until']);
      }
    }
    if ($from_granularity && $until_granularity && $from_granularity != $until_granularity) {
      $this->errors[] = new views_oai_pmh_error_bad_value('until', $args['until']);
    }
    else {
      if ($from_granularity) {
        $this->from = $args['from'];
      }
      if ($until_granularity) {
        $this->until = $args['until'];
      }
    }

    // Check identifier argument.
    if (isset($args['identifier'])) {
      $matches = array();
      if (preg_match('/^'. preg_quote($this->make_record_identifier_prefix()) . '([0-9]+)$/', $args['identifier'], $matches)) {
        $this->nid = $matches[1];
      }
      else {
        $this->errors[] = new views_oai_pmh_error_invalid_id($args['identifier']);
      }
    }
  }

  protected function check_date_format($date) {
    $matches = array();
    if (preg_match('/^([0-9]{4})-([0-9]{1,2})-([0-9]{1,2})T([0-9]{2}):([0-9]{2}):([0-9]{2})Z$/', $date, $matches)) {
      if (checkdate($matches[2], $matches[3], $matches[1])) {
        return 1;
      }
    }
    elseif (preg_match('/^([0-9]{4})-([0-9]{1,2})-([0-9]{1,2})$/', $date, $matches)) {
      if (checkdate($matches[2], $matches[3], $matches[1])) {
        return 2;
      }
    }
    return 0;
  }

  /**
   * Checks that the metadataPrefix argument matches a supported metadata
   * format.
   */
  protected function parse_metadata_prefix($args, $allowed_metadata_formats) {
    if (isset($args['metadataPrefix'])) {
      if (in_array($args['metadataPrefix'], $allowed_metadata_formats)
        && in_array($args['metadataPrefix'], views_oai_pmh_list_metadata_formats())) {
        $this->metadata_format = views_oai_pmh_get_metadata_format($args['metadataPrefix']);
        return;
      }
      $this->errors[] = new views_oai_pmh_error_cannot_disseminate_format($args['metadataPrefix']);
    }
  }
}
