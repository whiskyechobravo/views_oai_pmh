<?php

/**
 * Base class for an OAI-PMH error.
 */
class views_oai_pmh_error {
  public $code = '';
  protected $argument = '';
  protected $value = '';

  function __construct($code, $argument = '', $value = '') {
    $this->code = $code;
    $this->argument = $argument;
    $this->value = $value;
  }

  /**
   * Returns a generic message, normally overridden by subclasses.
   */
  function get_message() {
    $message = array();
    $message[] = t('Error: @code.', array('@code' => $this->code));
    if ($this->argument) {
      $message[] = t('Argument: @arg.', array('@arg' => $this->argument));
    }
    if ($this->value) {
      $message[] = t('Value: @value.', array('@value' => $this->value));
    }
    return implode(' ', $message);
  }
}


class views_oai_pmh_error_missing_verb extends views_oai_pmh_error {
  function __construct() {
    parent::__construct('badVerb');
  }

  function get_message() {
    return t('The OAI-PMH verb is missing.');
  }
}


class views_oai_pmh_error_bad_verb extends views_oai_pmh_error {
  function __construct() {
    parent::__construct('badVerb');
  }

  function get_message() {
    return t('Illegal OAI-PMH verb.');
  }
}


class views_oai_pmh_error_exclusive_argument extends views_oai_pmh_error {
  function __construct($argument) {
    parent::__construct('badArgument', $argument);
  }

  function get_message() {
    return t("The usage of '@arg' as an argument allows no other arguments.", array('@arg' => $this->argument));
  }
}


class views_oai_pmh_error_missing_argument extends views_oai_pmh_error {
  function __construct($argument) {
    parent::__construct('badArgument', $argument);
  }

  function get_message() {
    return t("The required argument '@arg' is missing.", array('@arg' => $this->argument));
  }
}


class views_oai_pmh_error_bad_argument extends views_oai_pmh_error {
  function __construct($argument) {
    parent::__construct('badArgument', $argument);
  }

  function get_message() {
    return t("The argument '@arg' is invalid with this verb.", array('@arg' => $this->argument));
  }
}


class views_oai_pmh_error_no_set_hierarchy extends views_oai_pmh_error {
  function __construct() {
    parent::__construct('noSetHierarchy');
  }

  function get_message() {
    return t('This repository does not support sets.');
  }
}


class views_oai_pmh_error_bad_value extends views_oai_pmh_error {
  function __construct($argument, $value) {
    parent::__construct('badArgument', $argument, $value);
  }

  function get_message() {
    return t("Illegal value '@value' for the argument '@arg'.", array('@arg' => $this->argument, '@value' => $this->value));
  }
}


class views_oai_pmh_error_invalid_id extends views_oai_pmh_error {
  function __construct($value) {
    parent::__construct('idDoesNotExist', '', $value);
  }

  function get_message() {
    return t("The value of identifier '@value' is invalid in this repository.", array('@value' => $this->value));
  }
}


class views_oai_pmh_error_unknown_id extends views_oai_pmh_error {
  function __construct($value) {
    parent::__construct('idDoesNotExist', '', $value);
  }

  function get_message() {
    return t("The value of identifier '@value' is unknown in this repository.", array('@value' => $this->value));
  }
}


class views_oai_pmh_error_cannot_disseminate_format extends views_oai_pmh_error {
  function __construct($value) {
    parent::__construct('cannotDisseminateFormat', '', $value);
  }

  function get_message() {
    return t("The metadata prefix '@value' is not supported by this repository.", array('@value' => $this->value));
  }
}


class views_oai_pmh_error_bad_resumption_token extends views_oai_pmh_error {
  function __construct($value) {
    parent::__construct('badResumptionToken', '', $value);
  }

  function get_message() {
    return t("The resumptionToken '@value' is invalid or has already expired.", array('@value' => $this->value));
  }
}


class views_oai_pmh_error_no_records_match extends views_oai_pmh_error {
  function __construct() {
    parent::__construct('noRecordsMatch');
  }

  function get_message() {
    return t('No records match the request criteria.');
  }
}
