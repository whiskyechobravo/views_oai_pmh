<?php

/**
 * Definition of the OAI Learning Objects Metadata (LOM) data format.
 */
class views_oai_pmh_format_oai_lom extends views_oai_pmh_format {
  public function __construct() {
    parent::__construct('oai_lom', t('Learning Objects Metadata (LOM)'));

    $this->schema = 'http://ltsc.ieee.org/xsd/lomv1.0/lom.xsd';
    $this->metadata_namespace = 'http://ltsc.ieee.org/xsd/LOM';

    $this->root_element = 'oai_lom:lom';
    $this->root_attributes = array(
      'xmlns:xsi' => 'http://www.w3.org/2001/XMLSchema-instance',
      'xsi:schemaLocation' => $this->metadata_namespace . '    ' . $this->schema,
      'xmlns:oai_lom' => $this->metadata_namespace,
      'xmlns:lom' => $this->metadata_namespace,
    );

    $this->attributes = array(
      // general
      'oai_lom:general/oai_lom:title/oai_lom:string' => array('language'),
      'oai_lom:general/oai_lom:description/oai_lom:string' => array('language'),
      'oai_lom:general/oai_lom:keyword/oai_lom:string' => array('language'),

      // educational
      'oai_lom:educational/oai_lom:typicalAgeRange/oai_lom:string' => array('language'),
      'oai_lom:educational/oai_lom:description/oai_lom:string' => array('language'),

      // rights
      'oai_lom:rights/oai_lom:description/oai_lom:string' => array('language'),

      // relation
      'oai_lom:relation/oai_lom:resource/oai_lom:description/oai_lom:string' => array('language'),

      // classification
      'oai_lom:classification/oai_lom:keyword/oai_lom:string' => array('language'),
    );

    $this->elements = array(
      'none' => t('None'),

      // attributes
      '@language' => t('(Attribute) Language'),

      // general
      'oai_lom:general' => 'General (Requires Template)',
      'oai_lom:general/oai_lom:identifier/oai_lom:catalog' => 'General > Identifier > Catalog',
      'oai_lom:general/oai_lom:identifier/oai_lom:entry' => 'General > Identifier > Entry',
      'oai_lom:general/oai_lom:title/oai_lom:string' => 'General > Title',
      'oai_lom:general/oai_lom:language' => 'General > Language',
      'oai_lom:general/oai_lom:description/oai_lom:string' => 'General > Description',
      'oai_lom:general/oai_lom:keyword' => 'General > Keyword (Requires Template)',
      'oai_lom:general/oai_lom:keyword/oai_lom:string' => 'General > Keyword > String',
      'oai_lom:general/oai_lom:structure/oai_lom:source' => 'General > Structure > Source',
      'oai_lom:general/oai_lom:structure/oai_lom:value' => 'General > Structure > Value',
      'oai_lom:general/oai_lom:aggregationLevel/oai_lom:source' => 'General > Aggregation Level > Source',
      'oai_lom:general/oai_lom:aggregationLevel/oai_lom:value' => 'General > Aggregation Level > Value',

      // lifeCycle
      'oai_lom:lifeCycle' => 'Life Cycle (Requires Template)',
      'oai_lom:lifeCycle/oai_lom:version/oai_lom:string' => 'Life Cycle > Version',
      'oai_lom:lifeCycle/oai_lom:status/oai_lom:source' => 'Life Cycle > Status > Source',
      'oai_lom:lifeCycle/oai_lom:status/oai_lom:value' => 'Life Cycle > Status > Value',
      'oai_lom:lifeCycle/oai_lom:contribute/oai_lom:role/oai_lom:source' => 'Life Cycle > Contribute > Role > Source',
      'oai_lom:lifeCycle/oai_lom:contribute/oai_lom:role/oai_lom:value' => 'Life Cycle > Contribute > Role > Value',
      'oai_lom:lifeCycle/oai_lom:contribute/oai_lom:entity' => 'Life Cycle > Contribute > Entity',

      // metaMetadata
      'oai_lom:metaMetadata' => 'Meta Metadata (Requires Template)',
      'oai_lom:metaMetadata/oai_lom:identifier/oai_lom:catalog' => 'Meta Metadata > Identifier > Catalog',
      'oai_lom:metaMetadata/oai_lom:identifier/oai_lom:entry' => 'Meta Metadata > Identifier > Entry',
      'oai_lom:metaMetadata/oai_lom:contribute/oai_lom:role/oai_lom:source' => 'Meta Metadata > Contribute > Role > Source',
      'oai_lom:metaMetadata/oai_lom:contribute/oai_lom:role/oai_lom:value' => 'Meta Metadata > Contribute > Role > Value',
      'oai_lom:metaMetadata/oai_lom:contribute/oai_lom:entity' => 'Meta Metadata > Contribute > Entity',
      'oai_lom:metaMetadata/oai_lom:metadataSchema' => 'Meta Metadata > Metadata Schema',
      'oai_lom:metaMetadata/oai_lom:language' => 'Meta Metadata > Language',

      // technical
      'oai_lom:technical' => 'Technical (Requires Template)',
      'oai_lom:technical/oai_lom:format' => 'Technical > Format',
      'oai_lom:technical/oai_lom:location' => 'Technical > Location',

      // educational
      'oai_lom:educational' => 'Educational (Requires Template)',
      'oai_lom:educational/oai_lom:interactivityType' => 'Educational > Interactivity (Requires Template)',
      'oai_lom:educational/oai_lom:interactivityType/oai_lom:source' => 'Educational > Interactivity > Source',
      'oai_lom:educational/oai_lom:interactivityType/oai_lom:value' => 'Educational > Interactivity > Value',
      'oai_lom:educational/oai_lom:learningResourceType' => 'Educational > Learning Resource Type (Requires Template)',
      'oai_lom:educational/oai_lom:learningResourceType/oai_lom:source' => 'Educational > Learning Resource Type > Source',
      'oai_lom:educational/oai_lom:learningResourceType/oai_lom:value' => 'Educational > Learning Resource Type > Value',
      'oai_lom:educational/oai_lom:interactivityLevel' => 'Educational > Interactivity Level (Requires Template)',
      'oai_lom:educational/oai_lom:interactivityLevel/oai_lom:source' => 'Educational > Interactivity Level > Source',
      'oai_lom:educational/oai_lom:interactivityLevel/oai_lom:value' => 'Educational > Interactivity Level > Value',
      'oai_lom:educational/oai_lom:intendedEndUserRole' => 'Educational > Intended End User Role (Requires Template)',
      'oai_lom:educational/oai_lom:intendedEndUserRole/oai_lom:source' => 'Educational > Intended End User Role > Source',
      'oai_lom:educational/oai_lom:intendedEndUserRole/oai_lom:value' => 'Educational > Intended End User Role > Value',
      'oai_lom:educational/oai_lom:context' => 'Educational > Context (Requires Template)',
      'oai_lom:educational/oai_lom:context/oai_lom:source' => 'Educational > Context > Source',
      'oai_lom:educational/oai_lom:context/oai_lom:value' => 'Educational > Context > Value',
      'oai_lom:educational/oai_lom:typicalAgeRange/oai_lom:string' => 'Educational > Typical Age Range',
      'oai_lom:educational/oai_lom:difficulty' => 'Educational > Difficulty (Requires Template)',
      'oai_lom:educational/oai_lom:difficulty/oai_lom:source' => 'Educational > Difficulty > Source',
      'oai_lom:educational/oai_lom:difficulty/oai_lom:value' => 'Educational > Difficulty > Value',
      'oai_lom:educational/oai_lom:typicalLearningTime/oai_lom:duration' => 'Educational > Typical Learning Time > Duration',
      'oai_lom:educational/oai_lom:description/oai_lom:string' => 'Educational > Description',
      'oai_lom:educational/oai_lom:language' => 'Educational > Educational > Language',

      // rights
      'oai_lom:rights' => 'Rights (Requires Template)',
      'oai_lom:rights/oai_lom:cost/oai_lom:source' => 'Rights > Cost > Source',
      'oai_lom:rights/oai_lom:cost/oai_lom:value' => 'Rights > Cost > Value',
      'oai_lom:rights/oai_lom:copyrightAndOtherRestrictions/oai_lom:source' => 'Rights > Copyright (+ Other) > Source',
      'oai_lom:rights/oai_lom:copyrightAndOtherRestrictions/oai_lom:value' => 'Rights > Copyright (+ Other) > Value',
      'oai_lom:rights/oai_lom:description/oai_lom:string' => 'Rights > Description',

      // relation
      'oai_lom:relation' => 'Relation (Requires Template)',
      'oai_lom:relation/oai_lom:kind/oai_lom:source' => 'Relation > Kind > Source',
      'oai_lom:relation/oai_lom:kind/oai_lom:value' => 'Relation > Kind > Value',
      'oai_lom:relation/oai_lom:resource/oai_lom:description/oai_lom:string' => 'Relation > Resource > Description',
      'oai_lom:relation/oai_lom:resource/oai_lom:identifier/oai_lom:catalog' => 'Relation > Resource > Identifier > Catalog',
      'oai_lom:relation/oai_lom:resource/oai_lom:identifier/oai_lom:entry' => 'Relation > Resource > Identifier > Entry',

      // classification
      'oai_lom:classification' => 'Classification (Requires Template)',
      'oai_lom:classification/oai_lom:purpose/oai_lom:source' => 'Classification > Purpose > Source',
      'oai_lom:classification/oai_lom:purpose/oai_lom:value' => 'Classification > Purpose > Value',
      'oai_lom:classification/oai_lom:keyword/oai_lom:string' => 'Classification > Keyword',
    );
  }
}
