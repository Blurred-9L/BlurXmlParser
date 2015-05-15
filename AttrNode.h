/**
 *  @file   AttrNode.h
 *  @author Blurred-9L
 */

#ifndef XML_PARSER_ATTR_NODE_H
#define XML_PARSER_ATTR_NODE_H

#include <string>
using std::string;

/**
 *  @class  AttrNode
 *
 *  @brief  The AttrNode class helps to structure a linked list of
 *          attributes that might be found inside a tag on the xml
 *          document.
 */
class AttrNode {
private:
    /// The attribute's name
    string name_;
    /// The attribute's value
    string value_;
    /// The next attribute in the list
    AttrNode * next_;
    
public:
    /// Constructor
    AttrNode(const string & name, const string & value);
    /// Destructor
    ~AttrNode();
    /// Gets name
    const string & name() const;
    /// Gets name
    string & name();
    /// Gets value
    const string & value() const;
    /// Gets value
    string & value();
    /// Gets next
    const AttrNode * next() const;
    /// Gets next
    AttrNode * next();
    /// Sets name
    void setName(const string & name);
    /// Sets value
    void setValue(const string & value);
    /// Sets next
    void setNext(AttrNode * nextNode);
    /// Prints node
    void print() const;
};

#endif /// NOT XML_PARSER_ATTR_NODE_H
