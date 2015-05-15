/**
 *  @file   TagNode.cpp
 *  @author Blurred-9L
 */

#include <iostream>
using std::cout;
using std::endl;

#include "TagNode.h"
#include "AttrNode.h"
#include "XmlContentManager.h"
#include "XmlObject.h"
#include "XmlObjectBuilder.h"
#include "XmlValue.h"

/// Prints spaces according to nesting level
static void print_spaces(int level);

/**
 *  @details    Creates a TagNode object and initializes with the given values.
 *
 *  @param[in]  name                The tag's name
 *  @param[in]  attrs               The tag's attribute list
 *  @param[in]  isVoid              Flag indicating if the tag is void
 *  @param[in]  isCloseTag          Flag indicating if the tag is closing.
 */
TagNode::TagNode(const string & name, AttrNode * attrs, bool isVoid, bool isCloseTag) :
    name_(name), contents_(), attrList(attrs), isVoid_(isVoid), isCloseTag_(isCloseTag)
{
}

/**
 *  @details    Releases resources used by the TagNode object.
 */
TagNode::~TagNode()
{
    int size = children.size();
    
    if (attrList != 0) {
        delete attrList;
    }
    for (int i = 0; i < size; i++) {
        if (children[i] != 0) {
            delete children[i];
        }
    }
}

/**
 *  @details    Get-method for the name member.
 *
 *  @return     A reference to the name member.
 */
const string & TagNode::name() const
{
    return name_;
}

/**
 *  @details    Get-method for the name member.
 *
 *  @return     A reference to the name member.
 */
string & TagNode::name()
{
    return name_;
}

/**
 *  @details    Get-method for the contents member.
 *
 *  @return     A reference to the contents member.
 */
const string & TagNode::contents() const
{
    return contents_;
}

/**
 *  @details    Get-method for the contents member.
 *
 *  @return     A reference to the contents member.
 */
string & TagNode::contents()
{
    return contents_;
}

/**
 *  @details    Get-method for the isVoid member.
 *
 *  @return     The value of the isVoid member.
 */
bool TagNode::isVoid() const
{
    return isVoid_;
}

/**
 *  @details    Get-method for the isCloseTag member.
 *
 *  @return     The value of the isCloseTag member.
 */
bool TagNode::isCloseTag() const
{
    return isCloseTag_;
}

/**
 *  @details    Set-method for the content data member.
 *
 *  @param[in]  data                The new content location data.
 */
void TagNode::setContentData(const ContentData & data)
{
    contentData = data;
}

/**
 *  @details    Adds a TagNode as the child of this node.
 *
 *  @param[in]  child               The child to add.
 */
void TagNode::addChild(TagNode * child)
{
    if (child != 0) {
        children.push_back(child);
    }
}

/**
 *  @details    Gets the number of children this node has.
 *
 *  @return     The value for the number of children of this node.
 */
int TagNode::nChildren() const
{
    return children.size();
}

/**
 *  @details    Tries to get the child at the given index
 *
 *  @param[in]  index               The index to use
 *
 *  @return     A pointer to the child TagNode or 0 if the index is beyond
 *              the range of the children vector.
 */
const TagNode * TagNode::getChild(int index) const
{
    int size = children.size();
    TagNode * child = 0;
    
    if (index >= 0 && index < size) {
        child = children[index];
    }
    
    return child;
}

/**
 *  @details    Tries to get the child at the given index
 *
 *  @param[in]  index               The index to use
 *
 *  @return     A pointer to the child TagNode or 0 if the index is beyond
 *              the range of the children vector.
 */
TagNode * TagNode::getChild(int index)
{
    int size = children.size();
    TagNode * child = 0;
    
    if (index >= 0 && index < size) {
        child = children[index];
    }
    
    return child;
}

/**
 *  @details    Adds an AttrNode at the start of the attributes list.
 *              If the given pointer is 0, then nothing is done.
 *
 *  @param[in]  attribute           The attribute to add.
 */
void TagNode::addAttribute(AttrNode * attribute)
{
    if (attribute != 0) {
        if (attrList != 0) {
            attribute->setNext(attrList);
        }
        attrList = attribute;
    }
}

/**
 *  @details    Get-method for the attribute list member.
 *
 *  @return     A pointer to the attribute list member.
 */
const AttrNode * TagNode::getAttributes() const
{
    return attrList;
}

/**
 *  @details    Get-method for the attribute list member.
 *
 *  @return     A pointer to the attribute list member.
 */
AttrNode * TagNode::getAttributes()
{
    return attrList;
}

/**
 *  @details    Prints the node to stdout. The node is printed
 *              by formatting each tag to be properly indented.
 *
 *  @param[in]  level               The level of indentation.
 */
void TagNode::print(int level) const
{
    AttrNode * attrNode = 0;
    int size = children.size();
    
    print_spaces(level);
    cout << "<" << name_;
    if (attrList != 0) {
        cout << " ";
        attrNode = attrList;
        while (attrNode != 0) {
            attrNode->print();
            attrNode = attrNode->next();
        }
    }
    if (isVoid_) {
        cout << "/>" << endl;
    } else {
        cout << ">" << endl;
        if (!contents_.empty()) {
            print_spaces(level + 1);
            cout << contents_ << endl;
        }
        for (int i = 0; i < size; i++) {
            children[i]->print(level + 1);
        }
        print_spaces(level);
        cout << "</" << name_ << ">" << endl;
    }
}

/**
 *  @details    Recursively travels through the xml document tree in order
 *              to obtain the content at the leaf nodes.
 *
 *  @param[in]  contentManager      The content manager from which to get the content.
 */
void TagNode::find_content(const XmlContentManager & contentManager)
{
    int curLine = contentData.startLine(), endLine = contentData.endLine();
    int startIndex = contentData.startIndex(), endIndex = contentData.endIndex();
    int nChildren = children.size();
    size_t firstChar, lastChar;
    const char * blank_charset = " \t\r\n\v\f";
    
    if (children.empty() && contents_.empty() && !isVoid_) {
        while (curLine < endLine) {
            contents_ += contentManager.getLine(curLine - 1).substr(startIndex);
            contents_ += "\n";
            curLine++;
            startIndex = 0;
        }
        contents_ += contentManager.getLine(curLine - 1).substr(startIndex, endIndex - startIndex);
        firstChar = contents_.find_first_not_of(blank_charset);
        lastChar = contents_.find_last_not_of(blank_charset);
        contents_.erase(contents_.begin(), contents_.begin() + firstChar);
        contents_.erase(contents_.begin() + lastChar + 1, contents_.end());
    }
    for (int i = 0; i < nChildren; i++) {
        children[i]->find_content(contentManager);
    }
}

/**
 *  @details    Transform this node into an representation that is easier to
 *              manipulate. The resulting XmlObject depends on the structure
 *              of the tag. If the tag does not have children, it becomes an
 *              XmlValue encapsulating this node. If it does have children, the
 *              result is either an XmlArray or XmlDictionary, choosing the former
 *              if all children have the same key or the latter if there are
 *              keys that differ.
 *
 *  @return     An XmlObject representing this node.
 */
XmlObject * TagNode::to_object()
{
    XmlObject * object = 0;
    int size;
    
    if (children.empty() || isVoid_) {
        cout << "Creating XmlValue for " << name_ << endl;
        object = new XmlValue(this);
    } else {
        size = children.size();
        XmlObjectBuilder builder;
        for (int i = 0; i < size; i++) {
            builder.add(children[i]->name(), children[i]->to_object());
        }
        cout << "Building for " << name_ << endl;
        object = builder.getXmlObject();
    }

    return object;
}

/**
 *  @details    Prints a set number of spaces to indent the nested
 *              tags of a TagNode.
 *
 *  @param[in]  level               The level of indentation.
 */
void print_spaces(int level)
{
    for (int i = 0; i < level; i++) {
        cout << "   ";
    }
}
