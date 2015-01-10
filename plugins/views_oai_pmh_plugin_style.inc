<?php

/**
 * @file
 * Contains the base OAI-PMH style plugin.
 */


class views_oai_pmh_plugin_style extends views_plugin_style {

  // The OAI-PMH request, represented by a views_oai_pmh_request object.
  protected $request;

  // The XML response document, a DOMDocument object.
  protected $xml;

  // The root element of the XML response, a DOMElement object.
  protected $xml_root;

  // The container element for the response.
  protected $xml_verb;


  //
  // Views plugin interface.
  //

  function option_definition() {
    $options = parent::option_definition();
    $options['enabled_formats'] = array('default' => array('oai_dc' => 'oai_dc'));
    $options['field_mappings'] = array('default' => array());
    return $options;
  }

  /**
   * Provide settings for this plugin.
   */
  function options_form(&$form, &$form_state) {
    // It is very important to call the parent function here:
    parent::options_form($form, $form_state);
    $handlers = $this->display->handler->get_handlers('field');
    if (empty($handlers)) {
      $form['error_markup'] = array(
        '#markup' => '<div class="error messages">' . t('You need at least one field before you can configure your table settings') . '</div>',
      );
      return;
    }

    $formats = views_oai_pmh_list_metadata_formats();

    // Add metadata format checkboxes.
    foreach ($formats as $id) {
      $format_options[$id] = $id . ' - ' . views_oai_pmh_get_metadata_format($id)->label;
    }
    $form['enabled_formats'] = array(
      '#type' => 'checkboxes',
      '#title' => t('OAI-PMH metadata formats'),
      '#description' => t('Select the metadata format(s) that you wish to publish. Note that the Dublin Core format must remain enabled as it is required by the OAI-PMH standard.'),
      '#default_value' => $this->options['enabled_formats'],
      '#options' => $format_options,
    );
    $form['enabled_formats']['oai_dc']['#disabled'] = TRUE; // 'oai_dc' is read-only.

    // Add mapping selectors.
    $fields = $this->display->handler->get_option('fields');
    $field_labels = $this->display->handler->get_field_labels();
    foreach ($formats as $id) {
      $format = views_oai_pmh_get_metadata_format($id);
      $form['field_mappings'][$id] = array(
        '#type' => 'fieldset',
        '#title' => $format->label,
        '#theme' => 'views_oai_pmh_field_mappings_form',
        '#states' => array(
          'visible' => array(
            ':input[name="style_options[enabled_formats][' . $id . ']"]' => array('checked' => TRUE),
          ),
        ),
      );
      foreach ($fields as $field_name => $info) {
        $form['field_mappings'][$id][$field_name] = array(
          '#type' => 'select',
          '#options' => $format->elements,
          '#default_value' => !empty($this->options['field_mappings'][$id][$field_name]) ? $this->options['field_mappings'][$id][$field_name] : '',
          '#title' => $field_labels[$field_name],
        );
      }
    }
  }

  function options_validate(&$form, &$form_state) {
    $form_state['values']['style_options']['enabled_formats']['oai_dc'] = 'oai_dc'; // 'oai_dc' is always on.
    parent::options_validate($form, $form_state);
  }

  function query() {
    global $base_url;

    if (!isset($this->request)) {
      // Initialize the request from URL arguments.
      $this->request = new views_oai_pmh_request(
        $base_url . base_path() . $this->display->handler->get_path(),
        array_filter($this->options['enabled_formats']),
        $this->view->live_preview);
    }

    // Perform the query action specified by the requested OAI-PMH verb.
    if ($this->request->verb && !$this->request->errors) {
      $callback = $this->request->callback . '_query';
      if (method_exists($this, $callback)) {
        call_user_func(array($this, $callback));
      }
    }

    if ($this->request->errors) {
      $this->view->executed = TRUE; // Avoid execution of the view's query.
    }
  }

  function render() {
    $this->xml_init();
    $this->xml_append_request();

    // Perform the render action specified by the requested OAI-PMH verb.
    if ($this->request->verb && !$this->request->errors) {
      $callback = $this->request->callback . '_render';
      if (method_exists($this, $callback)) {
        call_user_func(array($this, $callback));
      }
    }

    // Append all errors, if any, to the XML document.
    $this->xml_append_errors();

    $variables = array(
      'view' => $this->view,
      'options' => $this->options,
      'request' => $this->request,
      'xml' => $this->xml,
      'xml_root' => $this->xml_root,
      'xml_verb' => $this->xml_verb,
    );
    return theme('views_oai_pmh_response', $variables);
  }


  //
  // Internal query methods.
  //

  /**
   * Prepares the query for an 'Identify' OAI-PMH request.
   */
  protected function identify_query() {
    // We do not need the view's results to provide a response.
    $this->view->executed = TRUE;
  }

  /**
   * Prepares the query for a 'ListMetadataFormats' OAI-PMH request.
   */
  protected function list_metadata_formats_query() {
    // We do not need the view's results to provide a response.
    $this->view->executed = TRUE;
  }

  /**
   * Prepares the query for a 'ListIdentifiers' OAI-PMH request.
   */
  protected function list_identifiers_query() {
    if ($this->request->resumption_token) {
      $this->load_resumption_token_and_resume_query();
    }
    else {
      $this->add_record_query_fields();
      $this->add_record_query_dates();
    }
  }

  /**
   * Prepares the query for a 'GetRecord' OAI-PMH request.
   */
  protected function get_record_query() {
    $this->add_record_query_fields();
    $this->view->query->add_where(0, 'node.nid', $this->request->nid, '=');
  }

  /**
   * Prepares the query for a 'ListRecords' OAI-PMH request.
   */
  protected function list_records_query() {
    if ($this->request->resumption_token) {
      $this->load_resumption_token_and_resume_query();
    }
    else {
      $this->add_record_query_fields();
      $this->add_record_query_dates();
    }
  }

  /**
   * Adds the fields needed for record retrieval to the view's query.
   */
  protected function add_record_query_fields() {
    $this->view->query->add_field('node', 'nid');
    $this->view->query->add_field('node', 'changed');
    $this->view->query->add_orderby('node', 'nid', 'ASC');
  }

  /**
   * Add the requested date range to the view's query.
   */
  protected function add_record_query_dates() {
    if ($this->request->from) {
      $this->view->query->add_where(0, 'node.changed', strtotime($this->request->from), '>=');
    }
    if ($this->request->until) {
      $this->view->query->add_where(0, 'node.changed', strtotime($this->request->until), '<=');
    }
  }

  protected function load_resumption_token_and_resume_query() {
    $cache = db_select('cache_views_oai_pmh', 'c')
      ->fields('c')
      ->condition('cid', $this->request->resumption_token, '=')
      ->condition('expire', time() - VIEWS_OAI_PMH_TOKEN_LIFETIME, '>')
      ->execute()
      ->fetchObject();

    if (isset($cache->data)) {
      $cache->data = unserialize($cache->data);
      if (is_array($cache->data) && $cache->data['verb'] == $this->request->verb) {
        $this->view->query = $cache->data['query'];

        // Offset the query.
        $this->view->query->pager->set_current_page($cache->data['current_page'] + 1);

        // Restore some of the request data.
        $this->request->metadata_format = views_oai_pmh_get_metadata_format($cache->data['metadata_prefix']);
        return;
      }
    }

    $this->request->errors[] = new views_oai_pmh_error_bad_resumption_token($this->request->resumption_token);
  }


  //
  // Internal render methods.
  //

  /**
   * Renders a response to the 'identify' OAI-PMH request.
   */
  protected function identify_render() {
    $this->xml_append_verb();

    $datestamp = db_query('SELECT MIN(changed) FROM {node}')->fetchField(); // TODO: Should use the view's query to get a more accurate value.
    $elements = array(
      'repositoryName' => $this->display->handler->options['title'],
      'baseURL' => $this->request->base_url,
      'protocolVersion' => '2.0',
      'adminEmail' => variable_get('site_mail', ini_get('sendmail_from')),
      'earliestDatestamp' => gmstrftime('%Y-%m-%dT%H:%M:%SZ', $datestamp),
      'deletedRecord' => 'no',
      'granularity' => 'YYYY-MM-DDThh:mm:ssZ',
      // TODO: 'compression' => 'gzip',
    );
    $this->xml_append_children($this->xml_verb, $elements);
  }

  /**
   * Renders a response to the 'ListMetadataFormats' OAI-PMH request.
   *
   * The request's 'identifier' argument, if present, is just ignored here
   * since the same formats are supported regardless of the requested node.
   */
  protected function list_metadata_formats_render() {
    $this->xml_append_verb();

    $formats = views_oai_pmh_list_metadata_formats();
    $enabled_formats = array_filter($this->options['enabled_formats']);
    foreach (array_intersect($formats, $enabled_formats) as $id) {
      $format = views_oai_pmh_get_metadata_format($id);
      $format_element = $this->xml->createElement('metadataFormat');
      $this->xml_verb->appendChild($format_element);
      $elements = array(
        'metadataPrefix' => $format->id,
        'schema' => $format->schema,
        'metadataNamespace' => $format->metadata_namespace,
      );
      $this->xml_append_children($format_element, $elements);
    }
  }

  /**
   * Renders a response to the 'ListIdentifiers' OAI-PMH request.
   */
  protected function list_identifiers_render() {
    if ($this->view->result) {
      $this->xml_append_verb();

      foreach ($this->view->result as $row_index => $row) {
        $this->append_record_header($this->xml_verb, $row_index, $row);
      }

      $this->save_resumption_token();
    }
    else {
      $this->request->errors[] = new views_oai_pmh_error_no_records_match();
    }
  }

  /**
   * Renders a response to the 'GetRecord' OAI-PMH request.
   */
  protected function get_record_render() {
    if ($this->view->result && ($row = $this->view->result[0])) {
      $this->xml_append_verb();
      $record = $this->xml->createElement('record');
      $this->xml_verb->appendChild($record);
      $this->append_record_header($record, 0, $row);
      $this->append_record_metadata($record, 0, $row);
    }
    else {
      $this->request->errors[] = new views_oai_pmh_error_unknown_id($this->request->original_args['identifier']);
    }
  }

  /**
   * Renders a response to the 'ListRecords' OAI-PMH request.
   */
  protected function list_records_render() {
    if ($this->view->result) {
      $this->xml_append_verb();

      foreach ($this->view->result as $row_index => $row) {
        $record = $this->xml->createElement('record');
        $this->xml_verb->appendChild($record);
        $this->append_record_header($record, $row_index, $row);
        $this->append_record_metadata($record, $row_index, $row);
      }

      $this->save_resumption_token();
    }
    else {
      $this->request->errors[] = new views_oai_pmh_error_no_records_match();
    }
  }

  protected function append_record_header($parent, $row_index, $row) {
    $header_element = $this->xml->createElement('header');
    $parent->appendChild($header_element);
    $elements = array(
      'identifier' => $this->make_record_identifier($row->nid),
      'datestamp' => gmstrftime('%Y-%m-%dT%H:%M:%SZ', $row->node_changed),
    );
    $this->xml_append_children($header_element, $elements);
  }

  /**
   * Builds the core of a record's XML by using the mappings configured in
   * the view.
   */
  protected function append_record_metadata($parent, $row_index, $row) {
    $metadata_element = $this->xml->createElement('metadata');
    $parent->appendChild($metadata_element);
    $metadata_root = $this->xml->createElement($this->request->metadata_format->root_element);
    $metadata_element->appendChild($metadata_root);
    $this->xml_set_attributes($metadata_root, $this->request->metadata_format->root_attributes);

    // Available attributes, as an array of field ids keyed by attribute name.
    $available_attributes = array();

    foreach ($this->view->field as $field_name => $field) {
      list($mapping, $is_attribute) = $this->get_mapping($field_name);
      if ($is_attribute) {
        // Field is mapped to an attribute. Mark it is available for an upcoming element.
        $available_attributes[$mapping] = $field_name;
      }
      else {
        // Field is mapped to an element. Build the element in the XML tree.
        $used_attributes = array();
        $field_value = $this->get_field($row_index, $field_name);
        if ($field->options['exclude'] || empty($mapping) || (empty($field_value) && $field->options['hide_empty'])) {
          if (!empty($mapping)) {
            // Eat attributes that would have been consumed by the field's
            // mapping, had the field not been empty. This prevents attributes
            // from spilling to subsequent fields they were not intended for.
            $this->eat_attributes(explode('/', $mapping), $available_attributes);
          }
          continue; // Skip this field.
        }

        // Convert field value to an array.
        if (isset($field->multiple) && $field->multiple) {
          $field_values = explode($field->options['separator'], $field_value);
        }
        else {
          $field_values = array($field_value);
        }

        // Build XML elements for each value.
        $delta = 0; // Track position of current field values.
        foreach ($field_values as $field_value) {
          $mapping_path = array(); // Path of the current element in the mapping string.
          $element_path = array(); // Path of the current element, free of mapping codes.
          $nodes_in_element_path = array();
          $parent = $metadata_root;
          foreach (explode('/', $mapping) as $element) {
            $mapping_path[] = $element;
            if (implode('/', $mapping_path) != $mapping) {
              // We're not on a tree leaf. If the element has a '[]' suffix,
              // we'll try to work under an existing node whose position
              // matches $delta. If the element has a '[n]' suffix, we'll try
              // to work under an existing node at position 'n'. If neither
              // case applies, a new node will get created.
              $element_xpath_pattern = $this->prepare_tag($element, $delta);

              // Check if child exists.
              $xpath = new DOMXPath($this->xml);
              $existing_nodes = $xpath->query($element_xpath_pattern, $parent);

              if ($existing_nodes->length) {
                // Found an existing node matching the path. No need to create a new one.
                $element_node = $existing_nodes->item(0);
              }
              else {
                // Create a new node.
                $element_node = $this->xml->createElement($element);
                $parent->appendChild($element_node);
              }
            }
            else {
              // We're on a tree leaf. Create a new node no matter what, with the field value.
              $this->prepare_tag($element, $delta);
              $element_node = $this->xml->createElement($element, check_plain($field_value));
              $parent->appendChild($element_node);
            }

            $element_path[] = $element;
            $nodes_in_element_path[implode('/', $element_path)] = $element_node;
            $parent = $element_node; // Prepare next iteration.
          }

          $this->apply_attributes($row_index, $field, $delta, $nodes_in_element_path, $available_attributes, $used_attributes);
          $delta++; // Moving on to next field value.
        }

        // Remove attributes that have been consumed by this field.
        $available_attributes = array_diff_key($available_attributes, $used_attributes);
      }
    }
  }

  /**
   * Applies the available attributes to any of the given nodes, whenever a
   * node's path matches an attribute's path. Unused attributes may remain.
   *
   * Matching is starts with the leaf node, to avoid overwriting attributes
   * that might have already been applied to parent nodes.
   *
   * @param array $nodes
   *   A list of nodes belonging to a single path, sorted parents first, and
   *   keyed by their paths.
   */
  protected function apply_attributes($row_index, $field, $delta, $nodes, $available_attributes, &$used_attributes) {
    foreach (array_reverse($nodes) as $element_path => $element_node) {
      // Check if the metadata format supports any attributes on the current path.
      if (isset($this->request->metadata_format->attributes[$element_path]) && !empty($this->request->metadata_format->attributes[$element_path])) {
        // Check if any of our available attributes are among those supported by the metadata format.
        foreach ($available_attributes as $attribute_name => $attribute_field_name) {
          if (in_array($attribute_name, $this->request->metadata_format->attributes[$element_path])) {
            // Attribute applies. Let's add it!
            $attribute_field = $this->view->field[$attribute_field_name];
            $attribute_value = $this->get_field($row_index, $attribute_field_name);
            if (isset($attribute_field->multiple) && $attribute_field->multiple && isset($field->multiple) && $field->multiple) {
              // Find attribute delta matching the current field delta.
              $attribute_values = explode($attribute_field->options['separator'], $attribute_value);
              if (isset($attribute_values[$delta])) {
                $attribute_value = $attribute_values[$delta];
              }
            }
            $element_node->setAttribute($attribute_name, check_plain($attribute_value));
            $used_attributes[$attribute_name] = TRUE;

            // Remove this attribute from the available ones before proceeding with the remainder of the path.
            unset($available_attributes[$attribute_name]);
          }
        }
      }
    }
  }

  /**
   * Check whether any of the available attributes applies to elements in the
   * given path. Attributes that apply get removed from $available_attributes.
   */
  protected function eat_attributes($path, &$available_attributes) {
    // Loop through all subpaths, starting with the full path.
    while (!empty($path)) {
      $subpath = implode('/', $path);
      // Check if the metadata format supports any attributes on the current path.
      if (isset($this->request->metadata_format->attributes[$subpath]) && !empty($this->request->metadata_format->attributes[$subpath])) {
        // Check if any of our available attributes are among those supported by the metadata format.
        foreach ($available_attributes as $attribute_name => $attribute_field_name) {
          if (in_array($attribute_name, $this->request->metadata_format->attributes[$subpath])) {
            // Attribute applies. Let's remove it from the available ones!
            unset($available_attributes[$attribute_name]);
          }
        }
      }
      array_pop($path);
    }
  }

  /**
   * Given a tag originating from a mapping string, cleans it from mapping
   * codes (so it becomes proper for addition to the XML document), and returns
   * an xpath pattern useful to check if the element already exists.
   */
  protected static function prepare_tag(&$tag, $delta) {
    $matches = array();
    if (preg_match('/^(.+)\[([0-9]+)\]$/', $tag, $matches)) {
      // Mapping element has a '[0-9]' suffix. Use that directly as the xpath.
      $xpath_pattern = $tag;
      $tag = $matches[1]; // Replace with string without suffix.
    }
    elseif (preg_match('/^(.+)\[\]$/', $tag, $matches)) {
      // Mapping element has a '[]' suffix. Fill brackets with current delta.
      $tag = $matches[1]; // Replace with string without suffix.
      $xpath_pattern = $tag . '[' . ($delta + 1) . ']';
    }
    else {
      $xpath_pattern = $tag;
    }
    return $xpath_pattern;
  }

  /**
   * Saves a resumption token to the database and appends it to the XML.
   */
  protected function save_resumption_token() {
    if (get_class($this->view->query->pager) != 'views_plugin_pager_full') {
      watchdog('views_oai_pmh', 'Unexpected pager type. A full pager is required for harvesters to be able to retrieve all the data.', NULL, WATCHDOG_ERROR);
      return;
    }

    $items_per_page = $this->view->query->pager->get_items_per_page();
    $total_items = $this->view->query->pager->get_total_items();

    // Only generate the token if the list is incomplete.
    if ($total_items > $items_per_page) {
      $current_page = $this->view->query->pager->get_current_page();
      $total_pages = $this->view->query->pager->get_pager_total();
      $cursor = $items_per_page * $current_page;

      // When the list is complete, standard requires that an empty token is output.
      $token = ($current_page == $total_pages - 1) ? '' : md5(uniqid());

      // Add token output.
      $token_element = $this->xml->createElement('resumptionToken', $token);
      $this->xml_verb->appendChild($token_element);
      $token_element->setAttribute('completeListSize', $total_items);
      $token_element->setAttribute('cursor', $cursor);

      if ($token) {
        $expire = time() + VIEWS_OAI_PMH_TOKEN_LIFETIME;
        $token_element->setAttribute('expirationDate', gmstrftime('%Y-%m-%dT%H:%M:%SZ', $expire));

        // Save token to database.
        $data = array(
          'verb' => $this->request->verb,
          'metadata_prefix' => $this->request->metadata_format->id,
          'query' => $this->view->query,
          'current_page' => $current_page,
        );
        $fields = array(
          'serialized' => 1,
          'created' => $this->request->response_timestamp,
          'expire' => $expire,
          'data' => serialize($data),
          'cid' => $token
        );

        // Doing our own insert here because cache_set() is silently eating
        // max_allowed_packet errors and dropping cache inserts. Changing the
        // database configuration fixes the error, so let's make users aware of
        // it. Reference: http://drupal.org/node/542874.
        //
        // cache_set($token, $cache, 'cache_views_oai_pmh', time() + VIEWS_OAI_PMH_TOKEN_LIFETIME);
        db_insert('cache_views_oai_pmh')->fields($fields)->execute();
      }
    }
  }


  //
  // Internal XML building methods.
  //

  /**
   * Creates the DOMDocument for the OAI-PMH response, with elements that are
   * common to all responses.
   */
  protected function xml_init() {
    $this->xml = new DOMDocument('1.0', 'UTF-8');
    $this->xml->preserveWhitespace = FALSE;
    $this->xml->formatOutput = TRUE;

    $this->xml_root = $this->xml->createElement('OAI-PMH');
    $this->xml_root = $this->xml->appendChild($this->xml_root);
    $this->xml_root->setAttribute('xmlns', 'http://www.openarchives.org/OAI/2.0/');
    $this->xml_root->setAttribute('xmlns:xsi', 'http://www.w3.org/2001/XMLSchema-instance');
    $this->xml_root->setAttribute('xsi:schemaLocation', 'http://www.openarchives.org/OAI/2.0/   http://www.openarchives.org/OAI/2.0/OAI-PMH.xsd');
    $this->xml_append_children($this->xml_root, array('responseDate' => $this->request->response_date));
  }

  /**
   * Adds a node for the <request> element to the XML document.
   */
  protected function xml_append_request() {
    $request_element = $this->xml->createElement('request', $this->request->base_url);
    $this->xml_root->appendChild($request_element);

    // Provide attributes, unless a badVerb or badArgument error has occurred.
    if (!$this->request->is_bad()) {
      if ($this->request->verb) {
        $request_element->setAttribute('verb', $this->request->verb);
      }
      foreach ($this->request->original_args as $arg => $value) {
        $request_element->setAttribute($arg, $value);
      }
    }
  }

  /**
   * Adds a node for the OAI-PMH verb to the XML document. Successful responses
   * append their content to such nodes.
   */
  protected function xml_append_verb() {
    // Add verb element, e.g. <Identify>, <GetRecord>, etc.
    if (!$this->request->errors) {
      $this->xml_verb = $this->xml->createElement($this->request->verb);
      $this->xml_root->appendChild($this->xml_verb);
    }
  }

  /**
   * Adds all errors to the XML document.
   */
  protected function xml_append_errors() {
    foreach ($this->request->errors as $error) {
      $error_element = $this->xml->createElement('error', $error->get_message());
      $error_element->setAttribute('code', $error->code);
      $this->xml_root->appendChild($error_element);
    }
  }

  /**
   * Creates multiple children elements under a common parent in the XML
   * document. Key-value pairs from the $children array correspond to tag-value
   * pairs to create.
   */
  protected function xml_append_children($parent, $children) {
    foreach ($children as $tag => $value) {
      $element = $this->xml->createElement($tag, check_plain($value));
      $parent->appendChild($element);
    }
  }

  /**
   * Adds multiple attributes to a given element. Key-value pairs from the
   * $attributes array correspond to attribute-value pairs to set.
   */
  protected static function xml_set_attributes($element, $attributes) {
    foreach ($attributes as $name => $value) {
      $element->setAttribute($name, $value);
    }
  }

  //
  // Internal utility methods.
  //

  protected function make_record_identifier($id) {
    return $this->request->make_record_identifier_prefix() . $id;
  }

  /**
   * Get the mapping for a field.
   *
   * @return array
   *   An array where the first value is either a element path, or an attribute
   *   name the field is mapped to, and the second value a boolean that is TRUE
   *   if the first value is an attribute, FALSE otherwise.
   */
  protected function get_mapping($field_name) {
    if (isset($this->options['field_mappings'][$this->request->metadata_format->id][$field_name])) {
      $mapping = $this->options['field_mappings'][$this->request->metadata_format->id][$field_name];
      if ($mapping != 'none') {
        if ($mapping[0] == '@') {
          // Mapping is an attribute.
          return array(substr($mapping, 1), TRUE);
        }
        // Mapping is an element.
        return array($mapping, FALSE);
      }
    }
    return array('', FALSE);
  }
}

