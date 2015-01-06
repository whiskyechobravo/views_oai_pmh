<?php

/**
 * @file
 * Contains the OAI-PMH display plugin.
 */

class views_oai_pmh_plugin_display extends views_plugin_display_page {

  function get_style_type() {
    return 'views_oai_pmh';
  }

  function option_definition() {
    $options = parent::option_definition();

    // Overrides for standard stuff:
    $options['style_plugin']['default'] = 'views_oai_pmh_style';
    $options['defaults']['default']['style_plugin'] = FALSE;
    $options['defaults']['default']['style_options'] = FALSE;
    $options['row_plugin']['default'] = '';
    $options['defaults']['default']['row_plugin'] = FALSE;
    $options['defaults']['default']['row_options'] = FALSE;

    // Set default title.
    $options['title']['default'] = variable_get('site_name', 'OAI-PMH');
    $options['defaults']['default']['title'] = FALSE;

    return $options;
  }

  function options_summary(&$categories, &$options) {
    parent::options_summary($categories, $options);

    // Replace the inherited 'Page settings' label.
    $categories['page']['title'] = t('OAI-PMH settings');

    // Replace the default title label.
    $categories['title']['title'] = t('Repository name');
    $options['title']['title'] = t('Repository name');

    // Remove features that do not seem to make sense here.
    unset($options['menu']);
    unset($options['exposed_form']);
    unset($categories['exposed']);
  }

  /**
   * Provide the default form for setting options.
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    switch ($form_state['section']) {
      case 'title':
        $form['title']['#description'] = t("The repository name is given in response to OAI-PMH 'Identify' requests.");
        break;
    }
  }

  function uses_exposed() {
    return FALSE;
  }

  function uses_exposed_form_in_block() {
    return FALSE;
  }

  function displays_exposed() {
    return FALSE;
  }

  function use_ajax() {
    return FALSE;
  }

  function uses_breadcrumb() {
    return FALSE;
  }

  /**
   * Ensure that some settings are unique to this display. This is necessary
   * for settings that cannot be applied on the master display.
   */
  function defaultable_sections($section = NULL) {
    $sections = parent::defaultable_sections();
    unset($sections['title']);
    unset($sections['style_plugin']);
    unset($sections['style_options']);
    if ($section) {
      if (!empty($sections[$section])) {
        return $sections[$section];
      }
    }
    else {
      return $sections;
    }
  }

  /**
   * When used externally, this is how a view gets run and returns
   * data in the format required.
   */
  function execute() {
    // Let the world know that this is the page view we're using.
    views_set_page_view($this->view);

    // And now render the view.
    $output = $this->view->render();

    drupal_add_http_header('Content-Type', 'text/xml');
    print $output;
  }

  /**
   * Renders this display (actually delegates rendering to the style plugin).
   */
  function render() {
    return $this->view->style_plugin->render($this->view->result);
  }

  /**
   * Renders the preview.
   */
  function preview() {
    return '<pre>' . check_plain($this->view->render()) . '</pre>';
  }
}
