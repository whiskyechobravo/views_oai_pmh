Views OAI-PMH
=============

This Drupal 7 module allows the creation of OAI-PMH endpoints, exposing any
data the Views module has access to. This is a fork and a major overhaul of the
[Views OAI-PMH module](https://www.drupal.org/project/views_oai_pmh) for
Drupal.

The following metadata formats are supported:

* Dublin Core (oai_dc)
* Metadata Object Description Schema (mods)
* Learning Objects Metadata (oai_lom)
* Learning Resource Exchange (oai_lre)
* IMS Learning Objects Exchange (oai_ilox)

Other modules may provide their own metadata formats by implementing Drupal-
style hooks.


Why this fork?
--------------

This reworking was mainly motivated by the need to support a more complex
metadata format, namely the [Metadata Object Description Schema
(MODS)](http://www.loc.gov/standards/mods/). While trying to implement the
format, we encountered various issues which gradually led us to
refactor/rewrite most of the module. The changes outlined below should give a
good idea of the problems we wanted to solve.

Changes:

* Simpler architecture. Just two Views plugins (instead of 10): a display
  plugin and a style plugin.
* No more global variables. Lazy loading of metadata format definitions.
* Proper hooks for other modules to provide their own metadata formats.
* Mapping now uses its own settings data structure instead of hijacking a
  view's field labels.
* Attributes are no longer global to all elements. The same attribute may now
  appear with different values, on different tags within the same record.
* More robust XML building, using PHP's DOMDocument class.
* Logic out of the theming layer.
* Now impossible to disable the oai_dc metadata format, which is required by
  the OAI-PMH standard.
* New support for the Metadata Object Description Schema (MODS) format.
* Properly output the view's URL instead of the site's base URL in `<request>`
  tags.
* All errors are now detected and reported in the response, as required by the
  OAI-PMH standard, instead of stopping short after the first error. Also
  removed duplicate error messages and made record identifier checks more
  strict.


Why not publish on Drupal.org?
------------------------------

We will work with the authors of the original Views OAI-PMH. If they like this
version, perhaps it will replace the original version of the module. In the
meantime, it will be hosted on GitHub as Drupal.org does not allow multiple
modules with the same name.


Missing features
----------------

* Live preview for metadata formats other than oai_dc.
* Gzip compression.
* Handling for deleted records.
* Sets.


Requirements
------------

Required packages:

* [Drupal 7.x](https://www.drupal.org/project/drupal)
* [Views 7.x-3.x](https://www.drupal.org/project/views)

Optional packages:

* [Biblio 7.x-1.x](https://www.drupal.org/project/biblio)


Installing the module
---------------------

To install and enable Views OAI-PMH, please follow the usual [instructions for
module installation](https://www.drupal.org/documentation/install/modules-
themes/modules-7).


Upgrading from the original Views OAI-PMH
-----------------------------------------

Any views created with the original Views OAI-PMH 7.x-1.x or Views OAI-PMH
7.x-2.x will be incompatible. The mappings of the view fields to OAI-PMH
elements will have to be manually redone in the views. Backup your data before
upgrading!


Using the module
----------------

Anyone familiar with the Views module should quickly feel comfortable with
Views OAI-PMH. Outlined below are the steps required to create a new OAI-PMH
endpoint. Understanding Views concepts such as displays, fields and filters is
required.

1. Add a new view, with neither a page nor a block display, i.e. with just a
   "Master" display, showing content unsorted (Views OAI-PMH handles the
   sorting). Continue & edit this view.
2. Add an "OAI-PMH" display to the view.
3. Edit the Repository name. By default it is filled with the site's name. This
   name will appear in response to OAI-PMH "Identify" requests.
5. Add any desired filter criteria. These will limit what content is available
   from your new OAI-PMH endpoint.
6. Add any fields that provide the data that you wish to publish through OAI-
   PMH (for example, "Content: Title", "Content: Body", "Content: Post date").
   Some things to consider when configuring a field:
   * You may uncheck the "Create a label" option, as labels will not be part of
     the OAI-PMH output and will simply be ignored. You may still want to use
     labels for documentation purposes though.
   * In the "No results behavior" section, the "Hide if empty" option must be
     checked to avoid empty XML tags in the output.
   * In the "Rewrite results" section, check the "Strip HTML tags" option. HTML
     markup is not allowed in OAI-PMH elements.
   * Title fields must have the "Link this field to the original piece of
     content" option disabled.
   * Text fields must use the "Plain text" formatter. Again, HTML markup is not
     allowed in OAI-PMH elements.
   * Date fields must be formatted according to the requirements of the
     metadata format, e.g. W3CDTF.
   * Link fields and Entity Reference fields must not output links, just plain
     text, e.g. an URL, a title.
7. In the "Format" section, click the "Settings" link. This will take you to
   the "OAI-PMH Style options", where you'll find the mapping interface.
8. Enable the desired metadata formats for your new OAI-PMH endpoint. The
   Dublin Core (oai_dc) format is mandatory.
9. For each enabled format, a table is provided where you may associate each
   field that's been added to the display with an element in that metadata
   format. For example, in the "Dublin Core" table you could associate the
   "Content: Title" field with the "dc:title" element, the "Content: Body" with
   the "dc:description" element, and the "Content: Post date" with the
   "dc:date" element.
10. Configure a path for this display, such as "my-oai-pmh", in the "OAI-PMH
    Settings" section.
11. Save the view.
12. Optionally, you can test your new endpoint by going to
    http://re.cs.uct.ac.za/ and entering the absolute URL for your display,
    e.g. http://example.com/my-oai-pmh, in the "Enter the OAI baseURL" box, and
    then clicking the "Test the specified/selected baseURL" link (on the right
    side of the page).


### Dealing with attributes

Some metadata formats require that XML tags have specific attributes, such as a
"language" attribute. Views OAI-PMH allows you to map a field to an attribute:
Just select a target that's prefixed with "(Attribute)", e.g. "(Attribute)
Language".

Sometimes your content does not provide any data for those values, in which
case you can add to the view a "Global: Custom Text" field, which you'll be
able to map to an attribute.

A field that's mapped to an attribute must be positioned above the field that's
mapped to the element that uses the attribute. For example, to generate the
following MODS snippet:

    <language>
        <languageTerm authority="rfc3066">fr</languageTerm>
    </language>
    <name authority="local">
        <namePart>Smith, John</namePart>
    </name>

The view might use four fields (order is important):

* "Global: Custom text", configured with text "rfc3066"
* "Content: My language field", which will provide a language code, e.g. "fr"
* "Global: Custom text", configured with text "local"
* "Content: My author field", which will provide an author's name, e.g. "Smith,
  John".

Then the view would have the following MODS mappings:

* "Global: Custom text" mapped to "(Attribute) authority"
* "Content: My language field" mapped to "language > languageTerm"
* "Global: Custom text" mapped to "(Attribute) authority"
* "Content: My author field" mapped to "name (multiple) > namePart"

If it wasn't for the second "Global: Custom text" field being mapped to
"(Attribute) authority", there would be no "authority" attribute on the
`<name>` tag because the first attribute gets consumed by the `<languageTerm>`
tag, which appears before `<name>`. Indeed, any field that's mapped to an
attribute is *consumed* by the first encountered element that allows that
attribute, making that attribute value unavailable to any other elements
further down the list of fields.

Moreover, attributes are assigned depth-first to the target element. For
example, when building the output for the "name (multiple) > namePart" element,
the system first checks if the MODS metadata format allows an `authority`
attribute on a `<namePart>` tag. That attribute not being allowed on this tag,
the system then tries with the parent tag, `<name>`, finds that it is allowed
there, and therefore lets the `<name>` tag that consume the attribute.


### Dealing with multivalued fields

We usually need multivalued fields to generate multiple tags in the XML output,
one for each value. For example, a multivalued Entity Reference field might
generate the following oai_dc snippet:

    <dc:creator>Brooks, Kevin</dc:creator>
    <dc:creator>Nicci, French</dc:creator>
    <dc:creator>Mason, Matt</dc:creator>

For this to happen, the field must be configured appropriately in the view:

* Formatter: Title (no link)
* Multiple field settings > Display all values in the same row: Enabled.
* Multiple field settings > Display type: Simple separator
* Multiple field settings > Separator: Any character or character sequence that
  is unlikely to appear in a title.
* Multiple field settings > Display "all" value(s) starting from "0".
* No results behavior > Hide if empty: Enabled.

In the mapping interface, the field is then mapped to "dc:creator" (in the
Dublin Core table).

Unless noted otherwise in a mapping's target name, multiple values will
automatically generate multiple leaf nodes in the XML. For example, a
multivalued field that's mapped to "physicalDescription > form" in MODS will
generate a new `<form>` tag for each value, all under a common
`<physicalDescription>` parent, as in the following snippet:

    <physicalDescription>
        <form>text</form>
        <form>image</form>
        <form>video</form>
    </physicalDescription>

Some mappings, however, generate multiple nodes higher up in the XML tree. In
those cases, the label "(multiple)" indicates which tag will get repeated. The
following MODS snippet shows the output for a multivalued field that's mapped
to "name (multiple) > namePart":

    <name authority="local">
        <namePart>Brooks, Kevin</namePart>
    </name>
    <name authority="local">
        <namePart>Nicci, French</namePart>
    </name>
    <name authority="local">
        <namePart>Mason, Matt</namePart>
    </name>

In the above example, it is the `<name>` tag, rather than the leaf, that gets
repeated for each field value. Note that the "authority" attribute gets
repeated as well. As mentioned earlier, an attribute gets consumed by the first
encountered element that allows that attribute. When that element has multiple
values, the same attribute will apply to all of the values.

If a multivalued field is mapped to an attribute, however, the system will
instead try to assign each value to an element whose position with respect to
its siblings in the XML tree matches the value's index. It is thus possible to
output the following MODS snippet:

    <name authority="local" xlink:href="http://example.com/people/brooks-kevin">
        <namePart>Brooks, Kevin</namePart>
    </name>
    <name authority="local" xlink:href="http://example.com/people/nicci-french">
        <namePart>Nicci, French</namePart>
    </name>
    <name authority="local" xlink:href="http://example.com/people/mason-matt">
        <namePart>Mason, Matt</namePart>
    </name>

To generate the above output, the view might have the following three fields
(again, order is important):

* "Global: Custom text", configured for text "local"
* "Content: Authors", an Entity Reference field configured with the formatter
  "URL as plain text", and proper settings for a multivalued field.
* "Content: Authors", another instance of the same Entity Reference field, this
  time configured with the formatter "Title (no link)". Also configured with
  proper settings for a multivalued field.

Then the view would have the following MODS mappings:

* "Global: Custom text" mapped to "(Attribute) authority"
* "Content: Authors" mapped to "(Attribute) xlink:href"
* "Content: Authors" mapped to "name (multiple) > namePart"


### Default view

After the Views OAI-PMH module has been enabled, a new view called "OAI-PMH
endpoint" becomes available. You may review and edit it using Views UI, at
**Administer > Structure > Views**. That view provides a basic example for
mapping oai_dc elements to fields provided by the [Biblio
module](https://www.drupal.org/project/biblio).

The oai_dc metadata format is mandatory for OAI-PMH compliance. How you map its
elements, however, will depend on your site's structure. If your site does not
use Biblio, for instance, you'll have to edit the view, or disable it and
create a new one, then add the required fields and configure the mappings.


Theming and templating
----------------------

It is possible to create field templates. This might be useful in some cases
where custom formatting of the field values is needed. You may find the
appropriate template filename by clicking on **Other > Theme > Information** in
your view, and locating the field in the list. However, you cannot provide any
XML markup in those templates, as their output will be escaped before inclusion
into the XML document.

If you need to manipulate the XML document, you may implement the
"views_oai_pmh_response" theme hook in your theme. This function receives,
among other arguments, a PHP DOMDocument object containing the XML tree of the
OAI-PMH response. For more details, see the default implementation,
`theme_views_oai_pmh_response()`, in views_oai_pmh.theme.inc.


Implementing new metadata formats
---------------------------------

Any module can provide additional metadata formats to Views OAI-PMH. This
requires implementing two hooks:

* `hook_views_oai_pmh_metadata_format_info()`

  This hook returns the OAI-PMH metadata formats supported by the module. It
  simply returns an array where each value is the identifier of a metadata
  format provided by the module, e.g. "oai_dc", "my_oai_format".

* `hook_views_oai_pmh_metadata_format()`

  This hook receives a metadata format identifier as argument and returns an
  instance of the metadata format object corresponding to that id. That
  object's class must be a subclass of the `views_oai_pmh_format` class, which
  you can find in `includes/format.inc`. You may also want to take a look at
  the files in `includes/formats` for example implementations.

Views OAI-PMH itself simply implements those two hooks. You can find these
implementations in `views_oai_pmh.module`.


Credits
-------

This project has been developed by [Whisky Echo
Bravo](http://whiskyechobravo.com/) with sponsorship from the [Consortium on
Electronic Literature (CELL)](http://eliterature.org/cell/) and [Laboratoire
NT2](http://nt2.uqam.ca/).

It builds upon prior work, [Views OAI-
PMH](https://www.drupal.org/project/views_oai_pmh) 7.x-1.x by [Ron
Jerome](https://www.drupal.org/user/54997), sponsored by the [Minnesota
Historical Society](http://www.mnhs.org/index.htm), and Views OAI-PMH 7.x-2.x
by [Austin Goudge](https://www.drupal.org/u/psycleinteractive), sponsored by
[The Open University](http://www.open.ac.uk/).
