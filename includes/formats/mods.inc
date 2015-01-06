<?php

/**
 * Definition of the OAI Metadata Object Description Schema (MODS) data format.
 */
class views_oai_pmh_format_mods extends views_oai_pmh_format {
  public function __construct() {
    parent::__construct('mods', t('Metadata Object Description Schema (MODS)'));

    $this->schema = 'http://www.loc.gov/standards/mods/v3/mods-3-5.xsd';
    $this->metadata_namespace = 'http://www.loc.gov/mods/v3';

    $this->root_element = 'mods';
    $this->root_attributes = array(
      'xmlns:xsi' => 'http://www.w3.org/2001/XMLSchema-instance',
      'xmlns' => $this->metadata_namespace,
      'xsi:schemaLocation' => $this->metadata_namespace . '    ' . $this->schema,
      'xmlns:xlink' => 'http://www.w3.org/1999/xlink',
    );

    $this->attributes = array(
      // abstract element.
      'abstract' => array('type', 'displayLabel', 'shareable', 'altRepGroup', 'altFormat', 'contentType', 'xlink:href', 'lang', 'xml:lang', 'script', 'transliteration'),

      // accessCondition element.
      'accessCondition' => array('type', 'displayLabel', 'altRepGroup', 'altFormat', 'contentType', 'xlink:href', 'lang', 'xml:lang', 'script', 'transliteration'),

      // classification element.
      'classification' => array('authority', 'authorityURI', 'valueURI', 'edition', 'displayLabel', 'usage', 'altRepGroup', 'lang', 'xml:lang', 'script', 'transliteration', 'generator'),

      // extension element.
      'extension' => array('displayLabel'),

      // genre element.
      'genre' => array('type', 'authority', 'authorityURI', 'valueURI', 'usage', 'displayLabel', 'altRepGroup', 'lang', 'xml:lang', 'script', 'transliteration'),

      // identifier element.
      'identifier' => array('type', 'displayLabel', 'invalid', 'altRepGroup', 'lang', 'xml:lang', 'script', 'transliteration', 'typeURI'),

      // language element.
      'language' => array('usage', 'objectPart', 'displayLabel', 'altRepGroup', 'lang', 'xml:lang', 'script', 'transliteration'),
      'language/languageTerm' => array('type', 'authority', 'authorityURI', 'valueURI', 'lang', 'xml:lang', 'script', 'transliteration'),
      'language/scriptTerm' => array('type', 'authority', 'authorityURI', 'valueURI', 'lang', 'xml:lang', 'script', 'transliteration'),

      // location element.
      'location' => array('displayLabel', 'altRepGroup', 'lang', 'xml:lang', 'script', 'transliteration'),
      'location/physicalLocation' => array('type', 'authority', 'authorityURI', 'valueURI', 'displayLabel', 'xlink:href', 'lang', 'xml:lang', 'script', 'transliteration'),
      'location/shelfLocator' => array('lang', 'xml:lang', 'script', 'transliteration'),
      'location/url' => array('displayLabel', 'dateLastAccessed', 'note', 'access', 'usage'),
      'location/holdingSimple' => array(),
      'location/holdingSimple/copyInformation' => array(),
      'location/holdingSimple/copyInformation/form' => array('type', 'authority', 'authorityURI', 'valueURI', 'ID', 'lang', 'xml:lang', 'script', 'transliteration'),
      'location/holdingSimple/copyInformation/subLocation' => array('lang', 'xml:lang', 'script', 'transliteration'),
      'location/holdingSimple/copyInformation/shelfLocator' => array('lang', 'xml:lang', 'script', 'transliteration'),
      'location/holdingSimple/copyInformation/electronicLocator' => array(),
      'location/holdingSimple/copyInformation/note' => array('type', 'displayLabel', 'xlink:href', 'ID', 'lang', 'xml:lang', 'script', 'transliteration'),
      'location/holdingSimple/copyInformation/enumerationAndChronology' => array('unitType', 'lang', 'xml:lang', 'script', 'transliteration'),
      'location/holdingExternal' => array(),

      // name element.
      'name' => array('type', 'authority', 'authorityURI', 'valueURI', 'usage', 'displayLabel', 'nameTitleGroup', 'altRepGroup', 'xlink:href', 'ID', 'lang', 'xml:lang', 'script', 'transliteration', 'etal'),
      'name/namePart' => array('type', 'lang', 'xml:lang', 'script', 'transliteration'),
      'name/displayForm' => array('lang', 'xml:lang', 'script', 'transliteration'),
      'name/affiliation' => array('lang', 'xml:lang', 'script', 'transliteration'),
      'name/role' => array(),
      'name/role/roleTerm' => array('type', 'authority', 'authorityURI', 'valueURI', 'lang', 'xml:lang', 'script', 'transliteration'),
      'name/description' => array('lang', 'xml:lang', 'script', 'transliteration'),
      'name/etal' => array('lang', 'xml:lang', 'script', 'transliteration'),

      // note element.
      'note' => array('type', 'displayLabel', 'altRepGroup', 'xlink:href', 'ID', 'lang', 'xml:lang', 'script', 'transliteration', 'typeURI'),

      // originInfo element.
      'originInfo' => array('eventType', 'displayLabel', 'altRepGroup', 'lang', 'xml:lang', 'script', 'transliteration'),
      'originInfo/place' => array('supplied'),
      'originInfo/place/placeTerm' => array('type', 'authority', 'authorityURI', 'valueURI', 'lang', 'xml:lang', 'script', 'transliteration'),
      'originInfo/publisher' => array('supplied', 'lang', 'xml:lang', 'script', 'transliteration'),
      'originInfo/dateIssued' => array('encoding', 'point', 'keyDate', 'qualifier', 'lang', 'xml:lang', 'script', 'transliteration'),
      'originInfo/dateCreated' => array('encoding', 'point', 'keyDate', 'qualifier', 'lang', 'xml:lang', 'script', 'transliteration'),
      'originInfo/dateCaptured' => array('encoding', 'point', 'keyDate', 'qualifier', 'lang', 'xml:lang', 'script', 'transliteration'),
      'originInfo/dateValid' => array('encoding', 'point', 'keyDate', 'qualifier', 'lang', 'xml:lang', 'script', 'transliteration'),
      'originInfo/dateModified' => array('encoding', 'point', 'keyDate', 'qualifier', 'lang', 'xml:lang', 'script', 'transliteration'),
      'originInfo/copyrightDate' => array('encoding', 'point', 'keyDate', 'qualifier', 'lang', 'xml:lang', 'script', 'transliteration'),
      'originInfo/dateOther' => array('type', 'encoding', 'point', 'keyDate', 'qualifier', 'lang', 'xml:lang', 'script', 'transliteration'),
      'originInfo/edition' => array('supplied', 'lang', 'xml:lang', 'script', 'transliteration'),
      'originInfo/issuance' => array(),
      'originInfo/frequency' => array('authority', 'authorityURI', 'valueURI', 'lang', 'xml:lang', 'script', 'transliteration'),

      // part element.
      'part' => array('type', 'order', 'displayLabel', 'altRepGroup', 'ID', 'lang', 'xml:lang', 'script', 'transliteration'),
      'part/detail' => array('type', 'level', 'lang', 'xml:lang', 'script', 'transliteration'),
      'part/detail/number' => array('lang', 'xml:lang', 'script', 'transliteration'),
      'part/detail/caption' => array('lang', 'xml:lang', 'script', 'transliteration'),
      'part/detail/title' => array(),
      'part/extent' => array('unit'),
      'part/extent/start' => array('lang', 'xml:lang', 'script', 'transliteration'),
      'part/extent/end' => array('lang', 'xml:lang', 'script', 'transliteration'),
      'part/extent/total' => array(),
      'part/extent/list' => array('lang', 'xml:lang', 'script', 'transliteration'),
      'part/date' => array('encoding', 'point', 'qualifier', 'lang', 'xml:lang', 'script', 'transliteration'),
      'part/text' => array('type', 'displayLabel', 'xlink:href', 'lang', 'xml:lang', 'script', 'transliteration'),

      // physicalDescription element.
      'physicalDescription' => array('displayLabel', 'altRepGroup', 'lang', 'xml:lang', 'script', 'transliteration', 'unit'),
      'physicalDescription/form' => array('type', 'authority', 'authorityURI', 'valueURI', 'lang', 'xml:lang', 'script', 'transliteration'),
      'physicalDescription/reformattingQuality' => array(),
      'physicalDescription/internetMediaType' => array('lang', 'xml:lang', 'script', 'transliteration'),
      'physicalDescription/extent' => array('supplied', 'lang', 'xml:lang', 'script', 'transliteration'),
      'physicalDescription/digitalOrigin' => array(),
      'physicalDescription/note' => array('type', 'displayLabel', 'lang', 'xml:lang', 'script', 'transliteration', 'typeURI'),

      // recordInfo element.
      'recordInfo' => array('displayLabel', 'altRepGroup', 'lang', 'xml:lang', 'script', 'transliteration'),
      'recordInfo/recordContentSource' => array('type', 'authority', 'authorityURI', 'valueURI'),
      'recordInfo/recordCreationDate' => array('encoding', 'point', 'keyDate', 'qualifier', 'lang', 'xml:lang', 'script', 'transliteration'),
      'recordInfo/recordChangeDate' => array('encoding', 'point', 'keyDate', 'qualifier', 'lang', 'xml:lang', 'script', 'transliteration'),
      'recordInfo/recordIdentifier' => array('source', 'lang', 'xml:lang', 'script', 'transliteration'),
      'recordInfo/recordOrigin' => array('lang', 'xml:lang', 'script', 'transliteration'),
      'recordInfo/languageOfCataloging' => array('objectPart', 'usage', 'displayLabel', 'altRepGroup'),
      'recordInfo/descriptionStandard' => array('authority', 'authorityURI', 'valueURI', 'lang', 'xml:lang', 'script', 'transliteration'),

      // relatedItem element.
      'relatedItem' => array('type', 'displayLabel', 'xlink:href', 'ID'),

      // subject element.
      'subject' => array('authority', 'authorityURI', 'valueURI', 'usage', 'displayLabel', 'altRepGroup', 'xlink:href', 'ID', 'lang', 'xml:lang', 'script', 'transliteration'),
      'subject/topic' => array('authority', 'authorityURI', 'valueURI', 'lang', 'xml:lang', 'script', 'transliteration'),
      'subject/geographic' => array('authority', 'authorityURI', 'valueURI', 'lang', 'xml:lang', 'script', 'transliteration'),
      'subject/temporal' => array('authority', 'authorityURI', 'valueURI', 'encoding', 'point', 'keyDate', 'lang', 'xml:lang', 'script', 'transliteration'),
      'subject/titleInfo' => array('type', 'authority', 'authorityURI', 'valueURI', 'usage', 'displayLabel', 'supplied', 'nameTitleGroup', 'altRepGroup', 'altFormat', 'contentType', 'xlink:href', 'ID', 'lang', 'xml:lang', 'script', 'transliteration', 'otherType'),
      'subject/titleInfo/title' => array('lang', 'xml:lang', 'script', 'transliteration'),
      'subject/titleInfo/subtitle' => array('lang', 'xml:lang', 'script', 'transliteration'),
      'subject/titleInfo/partNumber' => array('lang', 'xml:lang', 'script', 'transliteration'),
      'subject/titleInfo/partName' => array('lang', 'xml:lang', 'script', 'transliteration'),
      'subject/titleInfo/nonSort' => array('lang', 'xml:lang', 'script', 'transliteration'),
      'subject/name' => array('type', 'authority', 'authorityURI', 'valueURI', 'usage', 'displayLabel', 'nameTitleGroup', 'altRepGroup', 'xlink:href', 'ID', 'lang', 'xml:lang', 'script', 'transliteration', 'etal'),
      'subject/name/namePart' => array('type', 'lang', 'xml:lang', 'script', 'transliteration'),
      'subject/name/displayForm' => array('lang', 'xml:lang', 'script', 'transliteration'),
      'subject/name/affiliation' => array('lang', 'xml:lang', 'script', 'transliteration'),
      'subject/name/role' => array(),
      'subject/name/role/roleTerm' => array('type', 'authority', 'authorityURI', 'valueURI', 'lang', 'xml:lang', 'script', 'transliteration'),
      'subject/name/description' => array('lang', 'xml:lang', 'script', 'transliteration'),
      'subject/name/etal' => array('lang', 'xml:lang', 'script', 'transliteration'),
      'subject/genre' => array('authority', 'authorityURI', 'valueURI', 'lang', 'xml:lang', 'script', 'transliteration'),
      'subject/hierarchicalGeographic' => array('authority', 'authorityURI', 'valueURI'),
      'subject/hierarchicalGeographic/continent' => array('lang', 'xml:lang', 'script', 'transliteration'),
      'subject/hierarchicalGeographic/country' => array('lang', 'xml:lang', 'script', 'transliteration'),
      'subject/hierarchicalGeographic/province' => array('lang', 'xml:lang', 'script', 'transliteration'),
      'subject/hierarchicalGeographic/region' => array('lang', 'xml:lang', 'script', 'transliteration'),
      'subject/hierarchicalGeographic/state' => array('lang', 'xml:lang', 'script', 'transliteration'),
      'subject/hierarchicalGeographic/territory' => array('lang', 'xml:lang', 'script', 'transliteration'),
      'subject/hierarchicalGeographic/county' => array('lang', 'xml:lang', 'script', 'transliteration'),
      'subject/hierarchicalGeographic/city' => array('lang', 'xml:lang', 'script', 'transliteration'),
      'subject/hierarchicalGeographic/citySection' => array('lang', 'xml:lang', 'script', 'transliteration'),
      'subject/hierarchicalGeographic/island' => array('lang', 'xml:lang', 'script', 'transliteration'),
      'subject/hierarchicalGeographic/area' => array('lang', 'xml:lang', 'script', 'transliteration'),
      'subject/hierarchicalGeographic/extraterrestrialArea' => array('lang', 'xml:lang', 'script', 'transliteration'),
      'subject/cartographics' => array(),
      'subject/cartographics/coordinates' => array('lang', 'xml:lang', 'script', 'transliteration'),
      'subject/cartographics/scale' => array('lang', 'xml:lang', 'script', 'transliteration'),
      'subject/cartographics/projection' => array('lang', 'xml:lang', 'script', 'transliteration'),
      'subject/geographicCode' => array('authority', 'authorityURI', 'valueURI', 'lang', 'xml:lang', 'script', 'transliteration'),
      'subject/occupation' => array('authority', 'authorityURI', 'valueURI', 'lang', 'xml:lang', 'script', 'transliteration'),

      // tableOfContents element.
      'tableOfContents' => array('type', 'displayLabel', 'shareable', 'altRepGroup', 'altFormat', 'contentType', 'xlink:href', 'lang', 'xml:lang', 'script', 'transliteration'),

      // targetAudience element.
      'targetAudience' => array('authority', 'authorityURI', 'valueURI', 'displayLabel', 'altRepGroup', 'lang', 'script', 'transliteration'),

      // titleInfo element.
      'titleInfo' => array('type', 'authority', 'authorityURI', 'valueURI', 'usage', 'displayLabel', 'supplied', 'nameTitleGroup', 'altRepGroup', 'altFormat', 'contentType', 'xlink:href', 'ID', 'lang', 'xml:lang', 'script', 'transliteration', 'otherType'),
      'titleInfo/title' => array('lang', 'xml:lang', 'script', 'transliteration'),
      'titleInfo/subtitle' => array('lang', 'xml:lang', 'script', 'transliteration'),
      'titleInfo/partNumber' => array('lang', 'xml:lang', 'script', 'transliteration'),
      'titleInfo/partName' => array('lang', 'xml:lang', 'script', 'transliteration'),
      'titleInfo/nonSort' => array('lang', 'xml:lang', 'script', 'transliteration'),

      // typeOfResource element.
      'typeOfResource' => array('collection', 'manuscript', 'usage', 'displayLabel', 'altRepGroup'),
    );

    $this->elements = array(
      'none' => t('- None -'),

      // Attributes.
      '@access' => t('(Attribute) access'),
      '@altFormat' => t('(Attribute) altFormat'),
      '@altRepGroup' => t('(Attribute) altRepGroup'),
      '@authority' => t('(Attribute) authority'),
      '@authorityURI' => t('(Attribute) authorityURI'),
      '@collection' => t('(Attribute) collection'),
      '@contentType' => t('(Attribute) contentType'),
      '@dateLastAccessed' => t('(Attribute) dateLastAccessed'),
      '@displayLabel' => t('(Attribute) displayLabel'),
      '@encoding' => t('(Attribute) encoding'),
      '@etal' => t('(Attribute) etal'),
      '@eventType' => t('(Attribute) eventType'),
      '@generator' => t('(Attribute) generator'),
      '@ID' => t('(Attribute) ID'),
      '@invalid' => t('(Attribute) invalid'),
      '@keyDate' => t('(Attribute) keyDate'),
      '@lang' => t('(Attribute) lang'),
      '@level' => t('(Attribute) level'),
      '@manuscript' => t('(Attribute) manuscript'),
      '@nameTitleGroup' => t('(Attribute) nameTitleGroup'),
      '@note' => t('(Attribute) note'),
      '@objectPart' => t('(Attribute) objectPart'),
      '@order' => t('(Attribute) order'),
      '@point' => t('(Attribute) point'),
      '@qualifier' => t('(Attribute) qualifier'),
      '@script' => t('(Attribute) script'),
      '@shareable' => t('(Attribute) shareable'),
      '@source' => t('(Attribute) source'),
      '@supplied' => t('(Attribute) supplied'),
      '@transliteration' => t('(Attribute) transliteration'),
      '@type' => t('(Attribute) type'),
      '@typeURI' => t('(Attribute) typeURI'),
      '@unit' => t('(Attribute) unit'),
      '@unitType' => t('(Attribute) unitType'),
      '@usage' => t('(Attribute) usage'),
      '@valueURI' => t('(Attribute) valueURI'),
      '@xlink:href' => t('(Attribute) xlink:href'),
      '@xml:lang' => t('(Attribute) xml:lang'),

      // abstract element.
      'abstract' => 'abstract',

      // accessCondition element.
      'accessCondition' => 'accessCondition',

      // classification element.
      'classification' => 'classification',

      // extension element.
      'extension' => 'extension',

      // genre element.
      'genre' => 'genre',

      // identifier element.
      'identifier' => 'identifier',

      // language element.
      'language' => 'language',
      'language/languageTerm' => 'language > languageTerm',
      'language/scriptTerm' => 'language > scriptTerm',

      // location element.
      'location' => 'location',
      'location/physicalLocation' => 'location > physicalLocation',
      'location/shelfLocator' => 'location > shelfLocator',
      'location/url' => 'location > url',
      'location/holdingSimple' => 'location > holdingSimple',
      'location/holdingSimple/copyInformation' => 'location > holdingSimple > copyInformation',
      'location/holdingSimple/copyInformation/form' => 'location > holdingSimple > copyInformation > form',
      'location/holdingSimple/copyInformation/subLocation' => 'location > holdingSimple > copyInformation > subLocation',
      'location/holdingSimple/copyInformation/shelfLocator' => 'location > holdingSimple > copyInformation > shelfLocator',
      'location/holdingSimple/copyInformation/electronicLocator' => 'location > holdingSimple > copyInformation > electronicLocator',
      'location/holdingSimple/copyInformation/note' => 'location > holdingSimple > copyInformation > note',
      'location/holdingSimple/copyInformation/enumerationAndChronology' => 'location > holdingSimple > copyInformation > enumerationAndChronology',
      'location/holdingExternal' => 'location > holdingExternal',

      // name element.
      'name[]' => 'name (multiple)',
      'name[]/namePart' => 'name (multiple) > namePart',
      'name[]/displayForm' => 'name (multiple) > displayForm',
      'name[]/affiliation' => 'name (multiple) > affiliation',
      'name[]/role' => 'name (multiple) > role',
      'name[]/role/roleTerm' => 'name (multiple) > role > roleTerm',
      'name[]/description' => 'name (multiple) > description',
      'name[]/etal' => 'name (multiple) > etal',

      // note element.
      'note' => 'note',

      // originInfo element.
      'originInfo' => 'originInfo',
      'originInfo/place' => 'originInfo > place',
      'originInfo/place/placeTerm' => 'originInfo > place > placeTerm',
      'originInfo/publisher' => 'originInfo > publisher',
      'originInfo/dateIssued' => 'originInfo > dateIssued',
      'originInfo/dateCreated' => 'originInfo > dateCreated',
      'originInfo/dateCaptured' => 'originInfo > dateCaptured',
      'originInfo/dateValid' => 'originInfo > dateValid',
      'originInfo/dateModified' => 'originInfo > dateModified',
      'originInfo/copyrightDate' => 'originInfo > copyrightDate',
      'originInfo/dateOther' => 'originInfo > dateOther',
      'originInfo/edition' => 'originInfo > edition',
      'originInfo/issuance' => 'originInfo > issuance',
      'originInfo/frequency' => 'originInfo > frequency',

      // part element.
      'part' => 'part',
      'part/detail' => 'part > detail',
      'part/detail/number' => 'part > detail > number',
      'part/detail/caption' => 'part > detail > caption',
      'part/detail/title' => 'part > detail > title',
      'part/extent' => 'part > extent',
      'part/extent/start' => 'part > extent > start',
      'part/extent/end' => 'part > extent > end',
      'part/extent/total' => 'part > extent > total',
      'part/extent/list' => 'part > extent > list',
      'part/date' => 'part > date',
      'part/text' => 'part > text',

      // physicalDescription element.
      'physicalDescription' => 'physicalDescription',
      'physicalDescription/form' => 'physicalDescription > form',
      'physicalDescription/reformattingQuality' => 'physicalDescription > reformattingQuality',
      'physicalDescription/internetMediaType' => 'physicalDescription > internetMediaType',
      'physicalDescription/extent' => 'physicalDescription > extent',
      'physicalDescription/digitalOrigin' => 'physicalDescription > digitalOrigin',
      'physicalDescription/note' => 'physicalDescription > note',

      // recordInfo element.
      'recordInfo' => 'recordInfo',
      'recordInfo/recordContentSource' => 'recordInfo > recordContentSource',
      'recordInfo/recordCreationDate' => 'recordInfo > recordCreationDate',
      'recordInfo/recordChangeDate' => 'recordInfo > recordChangeDate',
      'recordInfo/recordIdentifier' => 'recordInfo > recordIdentifier',
      'recordInfo/recordOrigin' => 'recordInfo > recordOrigin',
      'recordInfo/languageOfCataloging' => 'recordInfo > languageOfCataloging',
      'recordInfo/descriptionStandard' => 'recordInfo > descriptionStandard',

      // relatedItem element.
      'relatedItem' => 'relatedItem',

      // subject element.
      'subject' => 'subject',
      'subject/topic' => 'subject > topic',
      'subject/geographic' => 'subject > geographic',
      'subject/temporal' => 'subject > temporal',
      'subject/titleInfo' => 'subject > titleInfo',
      'subject/titleInfo/title' => 'subject > titleInfo > title',
      'subject/titleInfo/subtitle' => 'subject > titleInfo > subtitle',
      'subject/titleInfo/partNumber' => 'subject > titleInfo > partNumber',
      'subject/titleInfo/partName' => 'subject > titleInfo > partName',
      'subject/titleInfo/nonSort' => 'subject > titleInfo > nonSort',
      'subject/name[]' => 'subject > name (multiple)',
      'subject/name[]/namePart' => 'subject > name (multiple) > namePart',
      'subject/name[]/displayForm' => 'subject > name (multiple) > displayForm',
      'subject/name[]/affiliation' => 'subject > name (multiple) > affiliation',
      'subject/name[]/role' => 'subject > name (multiple) > role',
      'subject/name[]/role/roleTerm' => 'subject > name (multiple) > role > roleTerm',
      'subject/name[]/description' => 'subject > name (multiple) > description',
      'subject/name[]/etal' => 'subject > name (multiple) > etal',
      'subject/genre' => 'subject > genre',
      'subject/hierarchicalGeographic' => 'subject > hierarchicalGeographic',
      'subject/hierarchicalGeographic/continent' => 'subject > hierarchicalGeographic > continent',
      'subject/hierarchicalGeographic/country' => 'subject > hierarchicalGeographic > country',
      'subject/hierarchicalGeographic/province' => 'subject > hierarchicalGeographic > province',
      'subject/hierarchicalGeographic/region' => 'subject > hierarchicalGeographic > region',
      'subject/hierarchicalGeographic/state' => 'subject > hierarchicalGeographic > state',
      'subject/hierarchicalGeographic/territory' => 'subject > hierarchicalGeographic > territory',
      'subject/hierarchicalGeographic/county' => 'subject > hierarchicalGeographic > county',
      'subject/hierarchicalGeographic/city' => 'subject > hierarchicalGeographic > city',
      'subject/hierarchicalGeographic/citySection' => 'subject > hierarchicalGeographic > citySection',
      'subject/hierarchicalGeographic/island' => 'subject > hierarchicalGeographic > island',
      'subject/hierarchicalGeographic/area' => 'subject > hierarchicalGeographic > area',
      'subject/hierarchicalGeographic/extraterrestrialArea' => 'subject > hierarchicalGeographic > extraterrestrialArea',
      'subject/cartographics' => 'subject > cartographics',
      'subject/cartographics/coordinates' => 'subject > cartographics > coordinates',
      'subject/cartographics/scale' => 'subject > cartographics > scale',
      'subject/cartographics/projection' => 'subject > cartographics > projection',
      'subject/geographicCode' => 'subject > geographicCode',
      'subject/occupation' => 'subject > occupation',

      // tableOfContents element.
      'tableOfContents' => 'tableOfContents',

      // targetAudience element.
      'targetAudience' => 'targetAudience',

      // titleInfo element.
      'titleInfo' => 'titleInfo',
      'titleInfo/title' => 'titleInfo > title',
      'titleInfo/subtitle' => 'titleInfo > subtitle',
      'titleInfo/partNumber' => 'titleInfo > partNumber',
      'titleInfo/partName' => 'titleInfo > partName',
      'titleInfo/nonSort' => 'titleInfo > nonSort',

      // typeOfResource element.
      'typeOfResource' => 'typeOfResource',
    );
  }
}
