<?php

/**
 * Definition of the OAI IMS Learning Objects Exchange (ILOX) data format.
 */
class views_oai_pmh_format_oai_ilox extends views_oai_pmh_format {
  public function __construct() {
    parent::__construct('oai_ilox', t('IMS Learning Objects Exchange (ILOX)'));

    $this->schema = 'http://www.imsglobal.org/xsd/imsloilox_v1p0_ilox_work_v1p0.xsd';
    $this->metadata_namespace = 'http://www.imsglobal.org/xsd/lodeilox_v1p0/digital_LO';

    $this->root_element = 'work';
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

      // description -> LOM -> relation
      'description/metadata/lom/relation/resource/description/string' => array('language'),

      // description -> LOM -> classification
      'description/metadata/lom/classification/keyword/string' => array('language'),

      // description -> LOM -> rights
      'description/metadata/lom/rights/description/string' => array('language'),
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
      'description[1]/facet/vocabularyID' => 'Description (1) > Facet > Vocabulary ID',
      'description[1]/facet/value' => 'Description (1) > Facet > Value',
      'description[1]/metadata/schema' => 'Description (1) > Metadata > Schema',

      // description -> LOM -> general
      'description[1]/metadata/schema' => 'Description (1) > Metadata > Schema',
      'description[1]/metadata/lom/general' => 'Description (1) > Metadata > LOM > General (Requires Template)',
      'description[1]/metadata/lom/general/identifier/catalog' => 'Description (1) > Metadata > LOM > General > Identifier > Catalog',
      'description[1]/metadata/lom/general/identifier/entry' => 'Description (1) > Metadata > LOM > General > Identifier > Entry',
      'description[1]/metadata/lom/general/title/string' => 'Description (1) > Metadata > LOM > General > Title',
      'description[1]/metadata/lom/general/language' => 'Description (1) > Metadata > LOM > General > Language',
      'description[1]/metadata/lom/general/description/string' => 'Description (1) > Metadata > LOM > General > Description',
      'description[1]/metadata/lom/general/keyword' => 'Description (1) > Metadata > LOM > General > Keyword (Requires Template)',
      'description[1]/metadata/lom/general/keyword/string' => 'Description (1) > Metadata > LOM > General > Keyword > String',
      'description[1]/metadata/lom/general/structure/source' => 'Description (1) > Metadata > LOM > General > Structure > Source',
      'description[1]/metadata/lom/general/structure/value' => 'Description (1) > Metadata > LOM > General > Structure > Value',
      'description[1]/metadata/lom/general/aggregationLevel/source' => 'Description (1) > Metadata > LOM > General > Aggregation Level > Source',
      'description[1]/metadata/lom/general/aggregationLevel/value' => 'Description (1) > Metadata > LOM > General > Aggregation Level > Value',

      // description -> LOM -> lifeCycle
      'description[1]/metadata/lom/lifeCycle' => 'Description (1) > Metadata > LOM > Lifecycle (Requires Template)',
      'description[1]/metadata/lom/lifeCycle/version/string' => 'Description (1) > Metadata > LOM > Lifecycle > Version',
      'description[1]/metadata/lom/lifeCycle/status/source' => 'Description (1) > Metadata > LOM > Lifecycle > Status > Source',
      'description[1]/metadata/lom/lifeCycle/status/value' => 'Description (1) > Metadata > LOM > Lifecycle > Status > Value',
      'description[1]/metadata/lom/lifeCycle/contribute/role/source' => 'Description (1) > Metadata > LOM > Lifecycle > Contribute > Role > Source',
      'description[1]/metadata/lom/lifeCycle/contribute/role/value' => 'Description (1) > Metadata > LOM > Lifecycle > Contribute > Role > Value',
      'description[1]/metadata/lom/lifeCycle/contribute/entity' => 'Description (1) > Metadata > LOM > Lifecycle > Contribute > Entity',

      // description -> LOM -> metaMetadata
      'description[1]/metadata/lom/metaMetadata' => 'Description (1) > Metadata > LOM > Meta Metadata (Requires Template)',
      'description[1]/metadata/lom/metaMetadata/identifier/catalog' => 'Description (1) > Metadata > LOM > Meta Metadata > Identifier > Catalog',
      'description[1]/metadata/lom/metaMetadata/identifier/entry' => 'Description (1) > Metadata > LOM > Meta Metadata > Identifier > Entry',
      'description[1]/metadata/lom/metaMetadata/contribute/role/source' => 'Description (1) > Metadata > LOM > Meta Metadata > Contribute > Role > Source',
      'description[1]/metadata/lom/metaMetadata/contribute/role/value' => 'Description (1) > Metadata > LOM > Meta Metadata > Contribute > Role > Value',
      'description[1]/metadata/lom/metaMetadata/contribute/entity' => 'Description (1) > Metadata > LOM > Meta Metadata > Contribute > Entity',
      'description[1]/metadata/lom/metaMetadata/metadataSchema' => 'Description (1) > Metadata > LOM > Meta Metadata > Metadata Schema',
      'description[1]/metadata/lom/metaMetadata/language' => 'Description (1) > Metadata > LOM > Meta Metadata > Language',

      // description -> LOM -> technical
      'description[1]/metadata/lom/technical' => 'Description (1) > Metadata > LOM > Technical (Requires Template)',
      'description[1]/metadata/lom/technical/format' => 'Description (1) > Metadata > LOM > Technical > Format',
      'description[1]/metadata/lom/technical/location' => 'Description (1) > Metadata > LOM > Technical > Location',

      // description -> LOM -> educational
      'description[1]/metadata/lom/educational/interactivityType' => 'Description (1) > Metadata > LOM > Educational > Interactivity (Requires Template)',
      'description[1]/metadata/lom/educational/interactivityType/source' => 'Description (1) > Metadata > LOM > Educational > Interactivity > Source',
      'description[1]/metadata/lom/educational/interactivityType/value' => 'Description (1) > Metadata > LOM > Educational > Interactivity > Value',
      'description[1]/metadata/lom/educational/learningResourceType' => 'Description (1) > Metadata > LOM > Educational > Learning Resource Type (Requires Template)',
      'description[1]/metadata/lom/educational/learningResourceType/source' => 'Description (1) > Metadata > LOM > Educational > Learning Resource Type > Source',
      'description[1]/metadata/lom/educational/learningResourceType/value' => 'Description (1) > Metadata > LOM > Educational > Learning Resource Type > Value',
      'description[1]/metadata/lom/educational/interactivityLevel' => 'Description (1) > Metadata > LOM > Educational > Interactivity Level (Requires Template)',
      'description[1]/metadata/lom/educational/interactivityLevel/source' => 'Description (1) > Metadata > LOM > Educational > Interactivity Level > Source',
      'description[1]/metadata/lom/educational/interactivityLevel/value' => 'Description (1) > Metadata > LOM > Educational > Interactivity Level > Value',
      'description[1]/metadata/lom/educational/intendedEndUserRole' => 'Description (1) > Metadata > LOM > Educational > Intended End User Role (Requires Template)',
      'description[1]/metadata/lom/educational/intendedEndUserRole/source' => 'Description (1) > Metadata > LOM > Educational > Intended End User Role > Source',
      'description[1]/metadata/lom/educational/intendedEndUserRole/value' => 'Description (1) > Metadata > LOM > Educational > Intended End User Role > Value',
      'description[1]/metadata/lom/educational/context' => 'Description (1) > Metadata > LOM > Educational > Context (Requires Template)',
      'description[1]/metadata/lom/educational/context/source' => 'Description (1) > Metadata > LOM > Educational > Context > Source',
      'description[1]/metadata/lom/educational/context/value' => 'Description (1) > Metadata > LOM > Educational > Context > Value',
      'description[1]/metadata/lom/educational/typicalAgeRange/string' => 'Description (1) > Metadata > LOM > Educational > Typical Age Range',
      'description[1]/metadata/lom/educational/difficulty' => 'Description (1) > Metadata > LOM > Educational > Difficulty (Requires Template)',
      'description[1]/metadata/lom/educational/difficulty/source' => 'Description (1) > Metadata > LOM > Educational > Difficulty > Source',
      'description[1]/metadata/lom/educational/difficulty/value' => 'Description (1) > Metadata > LOM > Educational > Difficulty > Value',
      'description[1]/metadata/lom/educational/typicalLearningTime/duration' => 'Description (1) > Metadata > LOM > Educational > Typical Learning Time > Duration',
      'description[1]/metadata/lom/educational/description/string' => 'Description (1) > Metadata > LOM > Educational > Description',
      'description[1]/metadata/lom/educational/language' => 'Description (1) > Metadata > LOM > Educational > Language',

      // description -> LOM -> relation
      'description[1]/metadata/lom/relation' => 'Description (1) > Metadata > LOM > Relation (Requires Template)',
      'description[1]/metadata/lom/relation/kind/source' => 'Description (1) > Metadata > LOM > Relation > Kind > Source',
      'description[1]/metadata/lom/relation/kind/value' => 'Description (1) > Metadata > LOM > Relation > Kind > Value',
      'description[1]/metadata/lom/relation/resource/description/string' => 'Description (1) > Metadata > LOM > Relation > Resource > Description',
      'description[1]/metadata/lom/relation/resource/identifier/catalog' => 'Description (1) > Metadata > LOM > Relation > Resource > Identifier > Catalog',
      'description[1]/metadata/lom/relation/resource/identifier/entry' => 'Description (1) > Metadata > LOM > Relation > Resource > Identifier > Entry',

      // description -> LOM -> classification
      'description[1]/metadata/lom/classification' => 'Description (1) > Metadata > LOM > Classification (Requires Template)',
      'description[1]/metadata/lom/classification/purpose/source' => 'Description (1) > Metadata > LOM > Classification > Purpose > Source',
      'description[1]/metadata/lom/classification/purpose/value' => 'Description (1) > Metadata > LOM > Classification > Purpose > Value',
      'description[1]/metadata/lom/classification/keyword/string' => 'Description (1) > Metadata > LOM > Classification > Keyword',

      // description
      'description[2]/facet/vocabularyID' => 'Description (2) > Facet > Vocabulary ID',
      'description[2]/facet/value' => 'Description (2) > Facet > Value',
      'description[2]/metadata/schema' => 'Description (2) > Metadata > Schema',

      // description -> LOM -> rights
      'description[2]/metadata/lom/rights' => 'Description (2) > Metadata > LOM > Rights (Requires Template)',
      'description[2]/metadata/lom/rights/cost/source' => 'Description (2) > Metadata > LOM > Rights > Cost > Source',
      'description[2]/metadata/lom/rights/cost/value' => 'Description (2) > Metadata > LOM > Rights > Cost > Value',
      'description[2]/metadata/lom/rights/copyrightAndOtherRestrictions/source' => 'Description (2) > Metadata > LOM > Rights > Copyright (+ Other) > Source',
      'description[2]/metadata/lom/rights/copyrightAndOtherRestrictions/value' => 'Description (2) > Metadata > LOM > Rights > Copyright (+ Other) > Value',
      'description[2]/metadata/lom/rights/description/string' => 'Description (2) > Metadata > LOM > Rights > Description',

      // expression
      'expression/dimension' => 'Expression > Dimension (Requires Template)',
      'expression/dimension/name/vocabularyID' => 'Expression > Dimension > Name > Vocabulary ID',
      'expression/dimension/name/value' => 'Expression > Dimension > Name > Value',
      'expression/dimension/parameter/vocabularyID' => 'Expression > Dimension > Parameter > Vocabulary ID',
      'expression/dimension/parameter/value' => 'Expression > Dimension > Parameter > Value',
      'expression/manifestation' => 'Expression > Manifestation (Requires Template)',
      'expression/manifestation/identifier/catalog' => 'Expression > Manifestation > Identifier > Catalog',
      'expression/manifestation/identifier/entry' => 'Expression > Manifestation > Identifier > Entry',
      'expression/manifestation/name/vocabulary' => 'Expression > Manifestation > Name > Vocabulary',
      'expression/manifestation/name/value' => 'Expression > Manifestation > Name > Value',
      'expression/manifestation/item/location/uri' => 'Expression > Manifestation > Item > Location > URI',
    );
  }
}
