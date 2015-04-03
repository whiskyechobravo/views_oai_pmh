<?php

function views_oai_pmh_views_default_views() {
  $view = new view();
  $view->name = 'oai_pmh_biblio';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'OAI-PMH Biblio';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Field: Biblio: Authors */
  $handler->display->display_options['fields']['biblio_authors']['id'] = 'biblio_authors';
  $handler->display->display_options['fields']['biblio_authors']['table'] = 'biblio';
  $handler->display->display_options['fields']['biblio_authors']['field'] = 'biblio_authors';
  $handler->display->display_options['fields']['biblio_authors']['label'] = '';
  $handler->display->display_options['fields']['biblio_authors']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['biblio_authors']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['biblio_authors']['biblio_label'] = 1;
  $handler->display->display_options['fields']['biblio_authors']['auth_category'] = '0';
  $handler->display->display_options['fields']['biblio_authors']['initialize'] = 0;
  /* Field: Biblio: Corporate Authors */
  $handler->display->display_options['fields']['biblio_corp_authors']['id'] = 'biblio_corp_authors';
  $handler->display->display_options['fields']['biblio_corp_authors']['table'] = 'biblio';
  $handler->display->display_options['fields']['biblio_corp_authors']['field'] = 'biblio_corp_authors';
  $handler->display->display_options['fields']['biblio_corp_authors']['label'] = '';
  $handler->display->display_options['fields']['biblio_corp_authors']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['biblio_corp_authors']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['biblio_corp_authors']['biblio_label'] = 1;
  $handler->display->display_options['fields']['biblio_corp_authors']['auth_category'] = '5';
  $handler->display->display_options['fields']['biblio_corp_authors']['initialize'] = 0;
  /* Field: Biblio: ISBN Number */
  $handler->display->display_options['fields']['biblio_isbn']['id'] = 'biblio_isbn';
  $handler->display->display_options['fields']['biblio_isbn']['table'] = 'biblio';
  $handler->display->display_options['fields']['biblio_isbn']['field'] = 'biblio_isbn';
  $handler->display->display_options['fields']['biblio_isbn']['label'] = '';
  $handler->display->display_options['fields']['biblio_isbn']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['biblio_isbn']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['biblio_isbn']['biblio_label'] = 1;
  /* Field: Biblio: Keywords */
  $handler->display->display_options['fields']['biblio_keywords']['id'] = 'biblio_keywords';
  $handler->display->display_options['fields']['biblio_keywords']['table'] = 'biblio';
  $handler->display->display_options['fields']['biblio_keywords']['field'] = 'biblio_keywords';
  $handler->display->display_options['fields']['biblio_keywords']['label'] = '';
  $handler->display->display_options['fields']['biblio_keywords']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['biblio_keywords']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['biblio_keywords']['biblio_label'] = 1;
  /* Field: Biblio: Publication date */
  $handler->display->display_options['fields']['biblio_year']['id'] = 'biblio_year';
  $handler->display->display_options['fields']['biblio_year']['table'] = 'biblio';
  $handler->display->display_options['fields']['biblio_year']['field'] = 'biblio_year';
  $handler->display->display_options['fields']['biblio_year']['label'] = '';
  $handler->display->display_options['fields']['biblio_year']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['biblio_year']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['biblio_year']['biblio_label'] = 1;
  /* Field: Biblio: Publication Language(s) */
  $handler->display->display_options['fields']['biblio_lang']['id'] = 'biblio_lang';
  $handler->display->display_options['fields']['biblio_lang']['table'] = 'biblio';
  $handler->display->display_options['fields']['biblio_lang']['field'] = 'biblio_lang';
  $handler->display->display_options['fields']['biblio_lang']['label'] = '';
  $handler->display->display_options['fields']['biblio_lang']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['biblio_lang']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['biblio_lang']['biblio_label'] = 1;
  /* Field: Biblio: Publisher */
  $handler->display->display_options['fields']['biblio_publisher']['id'] = 'biblio_publisher';
  $handler->display->display_options['fields']['biblio_publisher']['table'] = 'biblio';
  $handler->display->display_options['fields']['biblio_publisher']['field'] = 'biblio_publisher';
  $handler->display->display_options['fields']['biblio_publisher']['label'] = '';
  $handler->display->display_options['fields']['biblio_publisher']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['biblio_publisher']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['biblio_publisher']['biblio_label'] = 1;
  /* Field: Biblio: Secondary Title */
  $handler->display->display_options['fields']['biblio_secondary_title']['id'] = 'biblio_secondary_title';
  $handler->display->display_options['fields']['biblio_secondary_title']['table'] = 'biblio';
  $handler->display->display_options['fields']['biblio_secondary_title']['field'] = 'biblio_secondary_title';
  $handler->display->display_options['fields']['biblio_secondary_title']['label'] = '';
  $handler->display->display_options['fields']['biblio_secondary_title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['biblio_secondary_title']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['biblio_secondary_title']['biblio_label'] = 1;
  /* Field: Biblio: URL */
  $handler->display->display_options['fields']['biblio_url']['id'] = 'biblio_url';
  $handler->display->display_options['fields']['biblio_url']['table'] = 'biblio';
  $handler->display->display_options['fields']['biblio_url']['field'] = 'biblio_url';
  $handler->display->display_options['fields']['biblio_url']['label'] = '';
  $handler->display->display_options['fields']['biblio_url']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['biblio_url']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['biblio_url']['biblio_label'] = 1;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'biblio' => 'biblio',
  );

  /* Display: OAI-PMH */
  $handler = $view->new_display('views_oai_pmh', 'OAI-PMH', 'views_oai_pmh_1');
  $handler->display->display_options['title'] = 'Biblio Repository';
  $handler->display->display_options['style_plugin'] = 'views_oai_pmh_style';
  $handler->display->display_options['style_options']['enabled_formats'] = array(
    'oai_dc' => 'oai_dc',
    'mods' => 0,
    'oai_etdms' => 0,
    'oai_ilox' => 0,
    'oai_lom' => 0,
    'oai_lre' => 0,
  );
  $handler->display->display_options['style_options']['field_mappings'] = array(
    'oai_dc' => array(
      'title' => 'dc:title',
      'biblio_authors' => 'dc:creator',
      'biblio_corp_authors' => 'dc:creator',
      'biblio_isbn' => 'dc:identifier',
      'biblio_keywords' => 'dc:subject',
      'biblio_year' => 'dc:date',
      'biblio_lang' => 'dc:language',
      'biblio_publisher' => 'dc:publisher',
      'biblio_secondary_title' => 'dc:source',
      'biblio_url' => 'dc:identifier',
    ),
    'mods' => array(
      'title' => 'none',
      'biblio_authors' => 'none',
      'biblio_corp_authors' => 'none',
      'biblio_isbn' => 'none',
      'biblio_keywords' => 'none',
      'biblio_year' => 'none',
      'biblio_lang' => 'none',
      'biblio_publisher' => 'none',
      'biblio_secondary_title' => 'none',
      'biblio_url' => 'none',
    ),
    'oai_etdms' => array(
      'title' => 'none',
      'biblio_authors' => 'none',
      'biblio_corp_authors' => 'none',
      'biblio_isbn' => 'none',
      'biblio_keywords' => 'none',
      'biblio_year' => 'none',
      'biblio_lang' => 'none',
      'biblio_publisher' => 'none',
      'biblio_secondary_title' => 'none',
      'biblio_url' => 'none',
    ),
    'oai_ilox' => array(
      'title' => 'none',
      'biblio_authors' => 'none',
      'biblio_corp_authors' => 'none',
      'biblio_isbn' => 'none',
      'biblio_keywords' => 'none',
      'biblio_year' => 'none',
      'biblio_lang' => 'none',
      'biblio_publisher' => 'none',
      'biblio_secondary_title' => 'none',
      'biblio_url' => 'none',
    ),
    'oai_lom' => array(
      'title' => 'none',
      'biblio_authors' => 'none',
      'biblio_corp_authors' => 'none',
      'biblio_isbn' => 'none',
      'biblio_keywords' => 'none',
      'biblio_year' => 'none',
      'biblio_lang' => 'none',
      'biblio_publisher' => 'none',
      'biblio_secondary_title' => 'none',
      'biblio_url' => 'none',
    ),
    'oai_lre' => array(
      'title' => 'none',
      'biblio_authors' => 'none',
      'biblio_corp_authors' => 'none',
      'biblio_isbn' => 'none',
      'biblio_keywords' => 'none',
      'biblio_year' => 'none',
      'biblio_lang' => 'none',
      'biblio_publisher' => 'none',
      'biblio_secondary_title' => 'none',
      'biblio_url' => 'none',
    ),
  );
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['path'] = 'oai-biblio';

  return array('oai_pmh' => $view);
}