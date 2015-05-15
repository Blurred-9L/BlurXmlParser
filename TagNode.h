/**
 *  @file   TagNode.h
 *  @author Blurred-9L
 */

#ifndef XML_PARSER_TAG_NODE_H
#define XML_PARSER_TAG_NODE_H

#include <vector>
using std::vector;
#include <string>
using std::string;

#include "ContentData.h"

class AttrNode;
class XmlContentManager;
class XmlObject;

/**
 *  @class  TagNode
 *
 *  @brief  The TagNode class is the result of the parsing of an xml document,
 *          with each TagNode object representing a tag in the document.
 */
class TagNode {
private:
    /// The node's children
    vector<TagNode *> children;
    /// The node's name
    string name_;
    /// The node's contents
    string contents_;
    /// The node's attributes
    AttrNode * attrList;
    /// Flag for void tag node
    bool isVoid_;
    /// Flag for closing tag node
    bool isCloseTag_;
    /// Data used to extract content string
    ContentData contentData;
     
public:
    /// Constructor
    TagNode(const string & name, AttrNode * attrs, bool isVoid, bool isCloseTag);
    /// Destructor
    ~TagNode();
    /// Gets name
    const string & name() const;
    /// Gets name
    string & name();
    /// Gets contents
    const string & contents() const;
    /// Gets contents
    string & contents();
    /// Checks if tag is void
    bool isVoid() const;
    /// Checks if tag is closing
    bool isCloseTag() const;
    /// Sets content data
    void setContentData(const ContentData & data);
    /// Adds child
    void addChild(TagNode * child);
    /// Gets number of children
    int nChildren() const;
    /// Gets child
    const TagNode * getChild(int index) const;
    /// Gets child
    TagNode * getChild(int index);
    /// Adds attribute
    void addAttribute(AttrNode * attribute);
    /// Gets list of attributes
    const AttrNode * getAttributes() const;
    /// Gets list of attributes
    AttrNode * getAttributes();
    /// Prints node
    void print(int level) const;
    /// Finds contents for node
    void find_content(const XmlContentManager & contentManager);
    /// Represents node as XmlObject
    XmlObject * to_object();
};

#endif /// NOT XML_PARSER_TAG_NODE_H
