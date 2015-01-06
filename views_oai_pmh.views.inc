<?php

/**
 * @file
 * Views include file with views hooks.
 */

/**
 * Implementation of hook_views_plugins().
 */
function views_oai_pmh_views_plugins() {
  $plugins = array(
    'display' => array(
      'views_oai_pmh' => array(
        'title' => t('OAI-PMH'),
        'admin' => t('OAI-PMH'),
        'help' => t('Provide a feed using the OAI-PMH protocol.'),
        'handler' => 'views_oai_pmh_plugin_display',
        'path' => drupal_get_path('module', 'views_oai_pmh') . '/plugins',
        'uses hook menu' => TRUE,
        'use ajax' => FALSE,
        'use pager' => TRUE, // Full pager is needed to get the count query and to output the count in the resumption token.
        'use more' => FALSE,
        'accept attachments' => FALSE,
      ),
    ),
    'style' => array(
      'views_oai_pmh_style' => array(
        'title' => t('OAI-PMH'),
        'help' => t('Displays rows in OAI-PMH records.'),
        'handler' => 'views_oai_pmh_plugin_style',
        'path' => drupal_get_path('module', 'views_oai_pmh') . '/plugins',
        'theme' => 'views_oai_pmh_response',
        'uses row plugin' => FALSE,
        'uses row class' => FALSE,
        'uses fields' => TRUE,
        'uses options' => TRUE,
        'type' => 'views_oai_pmh',
      ),
    ),
  );

  return $plugins;
}
