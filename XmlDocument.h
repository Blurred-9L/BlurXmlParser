/**
 *  @file   XmlDocument.h
 *  @author Blurred-9L
 */

#ifndef XML_PARSER_XML_DOCUMENT_H
#define XML_PARSER_XML_DOCUMENT_H

#include "XmlContentManager.h"
#include "XmlParser.h"

class TagNode;
class XmlObject;

/**
 *  @class  XmlDocument
 *
 *  @brief  The XmlDocument class is the main class used when interpreting
 *          xml documents.
 */
class XmlDocument {
private:
    /// The XmlParser to parse the document
    XmlParser parser_;
    /// The XmlContentManager from which to extract content
    XmlContentManager contentManager_;
    /// The root of the XmlDocument
    TagNode * root;
    
    /// Constructor
    explicit XmlDocument(const char * filename);
    
public:
    /// Destructor
    ~XmlDocument();
    /// Gets XmlParser
    const XmlParser & parser() const;
    /// Gets XmlParser
    XmlParser & parser();
    /// Gets ContentManager
    const XmlContentManager & contentManager() const;
    /// Gets ContentManager
    XmlContentManager & contentManager();
    /// Gets root as XmlDictionary
    XmlObject * getDictionary();
    
    /// Builds an XmlDocument object
    static XmlDocument * open(const char * filename);
};

#endif /// NOT XML_PARSER_XML_DOCUMENT_H
