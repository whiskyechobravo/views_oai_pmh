<?php

/**
 * Definition of the Interoperability Metadata Standard for Electronic Theses
 * and Dissertations (ETD-MS) v1.1 data format.
 */
class views_oai_pmh_format_oai_etdms extends views_oai_pmh_format {
  public function __construct() {
    parent::__construct('oai_etdms', t('Interoperability Metadata Standard for Electronic Theses and
  Dissertations (ETD-MS)'));

    $this->schema = 'http://www.ndltd.org/standards/metadata/etdms/1.1/etdms11.xsd';

    $this->namespaces = array(
      'xsi' => 'http://www.w3.org/2001/XMLSchema-instance',
      'oai_etdms' => 'http://www.ndltd.org/standards/metadata/etdms/1.1/',
      'dc' => 'http://purl.org/dc/elements/1.1/',
      'dcterms' => 'http://purl.org/dc/terms/',
    );
    $this->metadata_namespace_prefix = 'oai_etdms';

    $this->root_element = 'thesis';
    $this->root_attributes = array(
      'xmlns:xsi' => $this->namespaces['xsi'],
      'xsi:schemaLocation' => $this->namespaces['oai_etdms'] . '  ' .
        $this->schema . '  ' .
        'http://purl.org/dc/elements/1.1/  ' .
        'http://www.ndltd.org/standards/metadata/etdms/1.1/etdmsdc.xsd  ' .
        'http://purl.org/dc/terms/  ' .
        'http://www.ndltd.org/standards/metadata/etdms/1.1/etdmsdcterms.xsd',
      'xmlns' => $this->namespaces['oai_etdms'],
      'xmlns:dc' => $this->namespaces['dc'],
      'xmlns:dcterms' => $this->namespaces['dcterms'],
    );

    $this->attributes = array(
      'dc:contributor'    => array('lang', 'translated', 'scheme', 'role'),
      'dc:coverage'       => array('lang', 'translated', 'scheme'),
      'dc:creator'        => array('lang', 'translated', 'scheme'),
      'dc:date'           => array('lang', 'translated', 'scheme'),
      'dc:description'    => array('lang', 'translated', 'scheme', 'abstract', 'note', 'release'),
      'dc:format'         => array('lang', 'translated', 'scheme'),
      'dc:identifier'     => array('lang', 'translated', 'scheme'),
      'dc:language'       => array('lang', 'translated', 'scheme'),
      'dc:publisher'      => array('lang', 'translated', 'scheme', 'country'),
      'dc:relation'       => array('lang', 'translated', 'scheme'),
      'dc:rights'         => array('lang', 'translated', 'scheme'),
      'dc:source'         => array('lang', 'translated', 'scheme'),
      'dc:title'          => array('lang', 'translated', 'scheme'),
      'dc:type'           => array('lang', 'translated', 'scheme'),
      'degree/discipline' => array('lang', 'translated', 'scheme'),
      'degree/grantor'    => array('lang', 'translated', 'scheme'),
      'degree/level'      => array('lang', 'translated', 'scheme'),
      'degree/name'       => array('lang', 'translated', 'scheme'),
    );

    $this->elements = array(
      'none'                => t('- None -'),
      '@role'               => t('(Attribute) contributor.role'),
      '@abstract'           => t('(Attribute) description.abstract'),
      '@note'               => t('(Attribute) description.note'),
      '@release'            => t('(Attribute) description.release'),
      '@country'            => t('(Attribute) publisher.country'),
      '@lang'               => t('(Common attribute) lang'),
      '@scheme'             => t('(Common attribute) scheme'),
      '@translated'         => t('(Common attribute) translated'),
      'dc:contributor'      => 'dc.contributor',
      'dc:coverage'         => 'dc.coverage',
      'dc:creator'          => 'dc.creator',
      'dc:date'             => 'dc.date',
      'dc:description'      => 'dc.description',
      'dc:format'           => 'dc.format',
      'dc:identifier'       => 'dc.identifier',
      'dc:language'         => 'dc.language',
      'dc:publisher'        => 'dc.publisher',
      'dc:relation'         => 'dc.relation',
      'dc:rights'           => 'dc.rights',
      'dc:source'           => 'dc.source',
      'dc:subject'          => 'dc.subject',
      'dc:title'            => 'dc.title',
      'dcterms:alternative' => 'dc.title.alternative',
      'dc:type'             => 'dc.type',
      'degree/discipline'   => 'thesis.degree.discipline',
      'degree/grantor'      => 'thesis.degree.grantor',
      'degree/level'        => 'thesis.degree.level',
      'degree/name'         => 'thesis.degree.name',
    );
  }
}
