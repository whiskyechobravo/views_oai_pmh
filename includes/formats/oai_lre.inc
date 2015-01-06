<?php

/**
 * Definition of the OAI Learning Resource Exchange (LRE) data format.
 */
class views_oai_pmh_format_oai_lre extends views_oai_pmh_format {
  public function __construct() {
    parent::__construct('oai_lre', t('Learning Resource Exchange (LRE)'));

    $this->schema = 'http://fire.eun.org/lode/imslorsltitm_v1p0.xsd';
    $this->metadata_namespace = 'http://www.imsglobal.org/xsd/imslorsltitm_v1p0';

    $this->root_element = 'expression';
    $this->root_attributes = array(
      'xmlns:xsi' => 'http://www.w3.org/2001/XMLSchema-instance',
      'xsi:schemaLocation' => $this->metadata_namespace . '    ' . $this->schema,
      'xmlns' => $this->metadata_namespace,
    );

    $this->attributes = array(
      // description -> LOM
      'description/metadata/lom' => array('xsi:schemaLocation', 'xmlns'),

      // description -> LOM -> general
      'description/metadata/lom/general/title/string' => array('language'),
      'description/metadata/lom/general/description/string' => array('language'),
      'description/metadata/lom/general/keyword/string' => array('language'),

      // description -> LOM -> educational
      'description/metadata/lom/educational/typicalAgeRange/string' => array('language'),
      'description/metadata/lom/educational/description/string' => array('language'),

      // description -> LOM -> rights
      'description/metadata/lom/rights/description/string' => array('language'),

      // description -> LOM -> relation
      'description/metadata/lom/relation/resource/description/string' => array('language'),

      // description -> LOM -> classification
      'description/metadata/lom/classification/keyword/string' => array('language'),
    );

    $this->elements = array(
      'none' => t('None'),

      // attributes
      '@language' => t('(Attribute) Language'),
      '@xsi:schemaLocation' => t('(Attribute) LOM XSI Schema Location'),
      '@xmlns' => t('(Attribute) LOM XML Namespace'),

      // identifier
      'identifier/catalog' => 'Identifier > Catalog',
      'identifier/entry' => 'Identifier > Entry',

      // description
      'description/facet/vocabularyID' => 'Description > Facet > Vocabulary ID',
      'description/facet/value' => 'Description > Facet > Value',

      // description -> LOM -> general
      'description/metadata/schema' => 'Description > Metadata > Schema',
      'description/metadata/lom/general' => 'Description > Metadata > LOM > General (Requires Template)',
      'description/metadata/lom/general/identifier/catalog' => 'Description > Metadata > LOM > General > Identifier > Catalog',
      'description/metadata/lom/general/identifier/entry' => 'Description > Metadata > LOM > General > Identifier > Entry',
      'description/metadata/lom/general/title/string' => 'Description > Metadata > LOM > General > Title',
      'description/metadata/lom/general/language' => 'Description > Metadata > LOM > General > Language',
      'description/metadata/lom/general/description/string' => 'Description > Metadata > LOM > General > Description',
      'description/metadata/lom/general/keyword' => 'Description > Metadata > LOM > General > Keyword (Requires Template)',
      'description/metadata/lom/general/keyword/string' => 'Description > Metadata > LOM > General > Keyword > String',
      'description/metadata/lom/general/structure/source' => 'Description > Metadata > LOM > General > Structure > Source',
      'description/metadata/lom/general/structure/value' => 'Description > Metadata > LOM > General > Structure > Value',
      'description/metadata/lom/general/aggregationLevel/source' => 'Description > Metadata > LOM > General > Aggregation Level > Source',
      'description/metadata/lom/general/aggregationLevel/value' => 'Description > Metadata > LOM > General > Aggregation Level > Value',

      // description -> LOM -> lifeCycle
      'description/metadata/lom/lifeCycle' => 'Description > Metadata > LOM > Lifecycle (Requires Template)',
      'description/metadata/lom/lifeCycle/version/string' => 'Description > Metadata > LOM > Lifecycle > Version',
      'description/metadata/lom/lifeCycle/status/source' => 'Description > Metadata > LOM > Lifecycle > Status > Source',
      'description/metadata/lom/lifeCycle/status/value' => 'Description > Metadata > LOM > Lifecycle > Status > Value',
      'description/metadata/lom/lifeCycle/contribute/role/source' => 'Description > Metadata > LOM > Lifecycle > Contribute > Role > Source',
      'description/metadata/lom/lifeCycle/contribute/role/value' => 'Description > Metadata > LOM > Lifecycle > Contribute > Role > Value',
      'description/metadata/lom/lifeCycle/contribute/entity' => 'Description > Metadata > LOM > Lifecycle > Contribute > Entity',

      // description -> LOM -> metaMetadata
      'description/metadata/lom/metaMetadata' => 'Description > Metadata > LOM > Meta Metadata (Requires Template)',
      'description/metadata/lom/metaMetadata/identifier/catalog' => 'Description > Metadata > LOM > Meta Metadata > Identifier > Catalog',
      'description/metadata/lom/metaMetadata/identifier/entry' => 'Description > Metadata > LOM > Meta Metadata > Identifier > Entry',
      'description/metadata/lom/metaMetadata/contribute/role/source' => 'Description > Metadata > LOM > Meta Metadata > Contribute > Role > Source',
      'description/metadata/lom/metaMetadata/contribute/role/value' => 'Description > Metadata > LOM > Meta Metadata > Contribute > Role > Value',
      'description/metadata/lom/metaMetadata/contribute/entity' => 'Description > Metadata > LOM > Meta Metadata > Contribute > Entity',
      'description/metadata/lom/metaMetadata/metadataSchema' => 'Description > Metadata > LOM > Meta Metadata > Metadata Schema',
      'description/metadata/lom/metaMetadata/language' => 'Description > Metadata > LOM > Meta Metadata > Language',

      // description -> LOM -> technical
      'description/metadata/lom/technical' => 'Description > Metadata > LOM > Technical (Requires Template)',
      'description/metadata/lom/technical/format' => 'Description > Metadata > LOM > Technical > Format',
      'description/metadata/lom/technical/location' => 'Description > Metadata > LOM > Technical > Location',

      // description -> LOM -> educational
      'description/metadata/lom/educational/interactivityType' => 'Description > Metadata > LOM > Educational > Interactivity (Requires Template)',
      'description/metadata/lom/educational/interactivityType/source' => 'Description > Metadata > LOM > Educational > Interactivity > Source',
      'description/metadata/lom/educational/interactivityType/value' => 'Description > Metadata > LOM > Educational > Interactivity > Value',
      'description/metadata/lom/educational/learningResourceType' => 'Description > Metadata > LOM > Educational > Learning Resource Type (Requires Template)',
      'description/metadata/lom/educational/learningResourceType/source' => 'Description > Metadata > LOM > Educational > Learning Resource Type > Source',
      'description/metadata/lom/educational/learningResourceType/value' => 'Description > Metadata > LOM > Educational > Learning Resource Type > Value',
      'description/metadata/lom/educational/interactivityLevel' => 'Description > Metadata > LOM > Educational > Interactivity Level (Requires Template)',
      'description/metadata/lom/educational/interactivityLevel/source' => 'Description > Metadata > LOM > Educational > Interactivity Level > Source',
      'description/metadata/lom/educational/interactivityLevel/value' => 'Description > Metadata > LOM > Educational > Interactivity Level > Value',
      'description/metadata/lom/educational/intendedEndUserRole' => 'Description > Metadata > LOM > Educational > Intended End User Role (Requires Template)',
      'description/metadata/lom/educational/intendedEndUserRole/source' => 'Description > Metadata > LOM > Educational > Intended End User Role > Source',
      'description/metadata/lom/educational/intendedEndUserRole/value' => 'Description > Metadata > LOM > Educational > Intended End User Role > Value',
      'description/metadata/lom/educational/context' => 'Description > Metadata > LOM > Educational > Context (Requires Template)',
      'description/metadata/lom/educational/context/source' => 'Description > Metadata > LOM > Educational > Context > Source',
      'description/metadata/lom/educational/context/value' => 'Description > Metadata > LOM > Educational > Context > Value',
      'description/metadata/lom/educational/typicalAgeRange/string' => 'Description > Metadata > LOM > Educational > Typical Age Range',
      'description/metadata/lom/educational/difficulty' => 'Description > Metadata > LOM > Educational > Difficulty (Requires Template)',
      'description/metadata/lom/educational/difficulty/source' => 'Description > Metadata > LOM > Educational > Difficulty > Source',
      'description/metadata/lom/educational/difficulty/value' => 'Description > Metadata > LOM > Educational > Difficulty > Value',
      'description/metadata/lom/educational/typicalLearningTime/duration' => 'Description > Metadata > LOM > Educational > Typical Learning Time > Duration',
      'description/metadata/lom/educational/description/string' => 'Description > Metadata > LOM > Educational > Description',
      'description/metadata/lom/educational/language' => 'Description > Metadata > LOM > Educational > Language',

      // description -> LOM -> rights
      'description/metadata/lom/rights' => 'Description > Metadata > LOM > Rights (Requires Template)',
      'description/metadata/lom/rights/cost/source' => 'Description > Metadata > LOM > Rights > Cost > Source',
      'description/metadata/lom/rights/cost/value' => 'Description > Metadata > LOM > Rights > Cost > Value',
      'description/metadata/lom/rights/copyrightAndOtherRestrictions/source' => 'Description > Metadata > LOM > Rights > Copyright (+ Other) > Source',
      'description/metadata/lom/rights/copyrightAndOtherRestrictions/value' => 'Description > Metadata > LOM > Rights > Copyright (+ Other) > Value',
      'description/metadata/lom/rights/description/string' => 'Description > Metadata > LOM > Rights > Description',

      // description -> LOM -> relation
      'description/metadata/lom/relation' => 'Description > Metadata > LOM > Relation (Requires Template)',
      'description/metadata/lom/relation/kind/source' => 'Description > Metadata > LOM > Relation > Kind > Source',
      'description/metadata/lom/relation/kind/value' => 'Description > Metadata > LOM > Relation > Kind > Value',
      'description/metadata/lom/relation/resource/description/string' => 'Description > Metadata > LOM > Relation > Resource > Description',
      'description/metadata/lom/relation/resource/identifier/catalog' => 'Description > Metadata > LOM > Relation > Resource > Identifier > Catalog',
      'description/metadata/lom/relation/resource/identifier/entry' => 'Description > Metadata > LOM > Relation > Resource > Identifier > Entry',

      // description -> LOM -> classification
      'description/metadata/lom/classification' => 'Description > Metadata > LOM > Classification (Requires Template)',
      'description/metadata/lom/classification/purpose/source' => 'Description > Metadata > LOM > Classification > Purpose > Source',
      'description/metadata/lom/classification/purpose/value' => 'Description > Metadata > LOM > Classification > Purpose > Value',
      'description/metadata/lom/classification/keyword/string' => 'Description > Metadata > LOM > Classification > Keyword',

      // manifestation
      'manifestation' => 'Manifestation (Requires Template)',
      'manifestation/identifier/catalog' => 'Manifestation > Identifier > Catalog',
      'manifestation/identifier/entry' => 'Manifestation > Identifier > Entry',
      'manifestation/name/vocabulary' => 'Manifestation > Name > Vocabulary',
      'manifestation/name/value' => 'Manifestation > Name > Value',
      'manifestation/item/identifier/catalog' => 'Manifestation > Item > Identifier > Catalog',
      'manifestation/item/identifier/entry' => 'Manifestation > Item > Identifier > Entry',
      'manifestation/item/location/uri' => 'Manifestation > Item > Location > URI',
    );
  }
}
