/**
 *  @file   XmlArray.h
 *  @author Blurred-9L
 */

#ifndef XML_PARSER_XML_ARRAY_H
#define XML_PARSER_XML_ARRAY_H

#include "XmlObject.h"

/**
 *  @class  XmlArray
 *
 *  @brief  Inherits from XmlObject to represent a set of tags on
 *          an xml document which all have the same key.
 */
class XmlArray : public XmlObject {
private:
    /// Array of XmlObjects
    XmlObject ** arrayData;
    /// Number of objects
    int nObjects;
    
public:
    /// Constructor
    XmlArray(XmlObject ** objects, int size);
    /// Destructor
    virtual ~XmlArray();
    /// Checks if XmlObject is XmlArray
    bool isArray() const;
    /// Gets size of array.
    int size() const;
    /// Gets value
    const XmlObject * get(int index) const;
    /// Gets value
    XmlObject * get(int index);
};

#endif /// NOT XML_PARSER_XML_ARRAY_H
