XmlParser
=========

A set of classes used to parse and interpret simple XML documents.

#### What can it do? ####

This XMLParser is not meant to be used as a completely reliable parser to all Xml documents. This is mainly becuase
it does not implement the xml specification. This was a project I did for fun, but if any of these classes help
somebody else code their own or extend their own parsers, that's good.

Because of the above reasons, the parser does not check for the xml tag at the start of the document, though this might
be changed in the future. It does however, to the extents of some tests that have been done; parse tags, void tags
and tags with attributes. It can also extract the content of each tag after parsing, however, a bit unlike the
xml specification which says that a tag's content includes all of its blank characters, the XmlParser strips the
contents string from any leading and trailing whitespace. It also does not replace escape sequences or support
different encodings (that means, no utf-8 or any other, just ascii).

Tag names are taken as is. What does this mean? Well, if a tag name is written as MyTag.SomeOtherStuff or
MyNamespace:OtherThing, those will be the names you will need to use when accessing the tags via the XmlWrapper or
the XmlDictionary.

Other things to take into consideration:
- The debug messages for the XmlParser haven't been removed yet.
- Some of the tests done (not present on the repository) resulted in the use of a greater amount of memory
  (around 1.7MiB for a 1.7KiB file) so be careful about memory usage.
  
If you want an example for the intended usage of the classes, you can check the file at Test/xmldoctest.cpp which
is the one that tests most of the classes.

#### Building ####

As of now, some classes are missing (those from the BlurDataStructures directory). Once those are uploaded, you
can build this project by using the provided makefile, just make sure both the BlurParser and BlurDataStructures
projects are either included on this project's directory or that a link to them is present.
