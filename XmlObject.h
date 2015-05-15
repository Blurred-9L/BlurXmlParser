/**
 *  @file   XmlObject.h
 *  @author Blurred-9L
 */

#ifndef XML_PARSER_XML_OBJECT_H
#define XML_PARSER_XML_OBJECT_H

/**
 *  @class  XmlObject
 *
 *  @brief  Base class used to represent the tags on an xml document
 *          as easier to manipulate objects.
 *
 *  @sa     XmlValue
 *  @sa     XmlArray
 *  @sa     XmlDictionary
 */
class XmlObject {
public:
    /// Constructor
    XmlObject();
    /// Destructor
    virtual ~XmlObject();
    /// Checks if XmlObject is XmlMixedDictionary
    virtual bool isMixedDictionary() const;
    /// Checks if XmlObject is XmlDictionary
    virtual bool isDictionary() const;
    /// Checks if XmlObject is XmlArray
    virtual bool isArray() const;
    /// Checks if XmlObject is XmlValue
    virtual bool isValue() const;
};

#endif /// NOT XML_PARSER_XML_OBJECT_H
