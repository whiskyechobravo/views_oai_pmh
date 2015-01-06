<?php

/**
 * Theme functions for Views OAI-PMH.
 */

/**
 * Themes the field mappings form.
 */
function theme_views_oai_pmh_field_mappings_form($variables) {
  $rows = array();
  foreach (element_children($variables['form']) as $field_name) {
    $title = $variables['form'][$field_name]['#title'];
    unset($variables['form'][$field_name]['#title']);
    $rows[] = array(
      $title,
      drupal_render($variables['form'][$field_name]),
    );
  }
  $header = array(t('View field'), t('!format element', array('!format' => $variables['form']['#title'])));
  return theme('table', array('header' => $header, 'rows' => $rows));
}

/**
 * Themes the XML response.
 *
 * Available variables:
 * - view: The view.
 * - options: The options of the view style.
 * - request: A views_oai_pmh_request object describing the parsed request
 *   arguments.
 * - xml: A DOMDocument object containing the response.
 * - xml_root: The DOMElement object at the root of the XML document.
 * - xml_verb: The DOMElement object at the root of the actual response to the
 *   OAI-PMH verb, e.g. <Identify>, <GetRecord>, etc. May be NULL on erroneous
 *   requests.
 */
function theme_views_oai_pmh_response($variables) {
  return $variables['xml']->saveXML();
}
