/**
 *  @file   XmlObjectBuilder.h
 *  @author Blurred-9L
 */

#ifndef XML_PARSER_XML_OBJECT_BUILDER_H
#define XML_PARSER_XML_OBJECT_BUILDER_H

#include <map>
using std::multimap;
#include <string>
using std::string;

class XmlObject;
class XmlArray;
class XmlDictionary;

/**
 *  @class  XmlObjectBuilder
 *
 *  @brief  The XmlObjectBuilder class allows easy building of XmlArray or
 *          XmlDictionary objects by collecting pairs of name tags and their
 *          related XmlObjects until they have to be instantiated as either
 *          collection.
 */
class XmlObjectBuilder {
private:
    /// The key-value map for XmlObjects
    multimap<string, XmlObject *> data;
    /// Flag indicating that all keys are unique
    bool allDifferent;
    /// Flag indicating that all keys are the same
    bool allEqual;
    /// Flag indicating that there are repeated keys
    bool repeatedKeys;
    
public:
    /// Constructor
    XmlObjectBuilder();
    /// Resets state to default
    void reset();
    /// Adds an element to the XmlObject
    void add(const string & key, XmlObject * object);
    /// Builds the XmlObject
    XmlObject * getXmlObject();
    
private:
    /// Builds XmlArray with the collected keys and objects
    XmlArray * buildXmlArray();
    /// Builds XmlDictionary with the collected keys and objects
    XmlDictionary * buildXmlDictionary();
    /// Builds a mixed XmlDictionary with the collected keys and objects 
    XmlDictionary * buildMixedDictionary();
};

#endif /// NOT XML_PARSER_XML_OBJECT_BUILDER_H
