<?php

/**
 * Definition of the OAI Dublin Core (DC) data format.
 */
class views_oai_pmh_format_oai_dc extends views_oai_pmh_format {
  public function __construct() {
    parent::__construct('oai_dc', t('Dublin Core'));

    $this->schema = 'http://www.openarchives.org/OAI/2.0/oai_dc.xsd';
    $this->metadata_namespace = 'http://www.openarchives.org/OAI/2.0/oai_dc/';

    $this->root_element = 'oai_dc:dc';
    $this->root_attributes = array(
      'xmlns:xsi' => 'http://www.w3.org/2001/XMLSchema-instance',
      'xsi:schemaLocation' => $this->metadata_namespace . '    ' . $this->schema,
      'xmlns:oai_dc' => $this->metadata_namespace,
      'xmlns:dc' => 'http://purl.org/dc/elements/1.1/',
    );

    $this->elements = array(
      'none'           => t('- None -'),
      'dc:title'       => 'dc:title',
      'dc:creator'     => 'dc:creator',
      'dc:subject'     => 'dc:subject',
      'dc:description' => 'dc:description',
      'dc:publisher'   => 'dc:publisher',
      'dc:contributor' => 'dc:contributor',
      'dc:date'        => 'dc:date',
      'dc:type'        => 'dc:type',
      'dc:format'      => 'dc:format',
      'dc:identifier'  => 'dc:identifier',
      'dc:source'      => 'dc:source',
      'dc:language'    => 'dc:language',
      'dc:relation'    => 'dc:relation',
      'dc:coverage'    => 'dc:coverage',
      'dc:rights'      => 'dc:rights',
    );
  }
}
