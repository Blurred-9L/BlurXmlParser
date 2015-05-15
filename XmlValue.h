/**
 *  @file   XmlValue.h
 *  @author Blurred-9L
 */

#ifndef XML_PARSER_XML_VALUE_H
#define XML_PARSER_XML_VALUE_H

#include "XmlObject.h"

class TagNode;

/**
 *  @class  XmlValue
 *
 *  @brief  Class inheriting from XmlObject to represent a leaf node
 *          on the xml document.
 */
class XmlValue : public XmlObject {
private:
    /// The related leaf TagNode
    TagNode * tag;
    
public:
    /// Constructor
    XmlValue(TagNode * tag);
    /// Destructor
    virtual ~XmlValue();
    /// Checks if XmlObject is XmlValue
    bool isValue() const;
    /// Gets content
    const string & content() const;
    /// Gets content
    string & content();
};

#endif /// NOT XML_PARSER_XML_VALUE_H
