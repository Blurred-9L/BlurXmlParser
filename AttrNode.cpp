/**
 *  @file   AttrNode.cpp
 *  @author Blurred-9L
 */

#include <iostream>
using std::cout;
using std::endl;

#include "AttrNode.h"

/**
 *  @details    Constructs an AttrNode object with the given name and value.
 *              Because the value string is usually surrounded by double quotes,
 *              if it starts and ends with a double-quote, these characters will
 *              be removed. No similar comparison is made for single quotes.
 *
 *  @param[in]  name                The attribute's name.
 *  @param[in]  value               The attribute's value.
 */
AttrNode::AttrNode(const string & name, const string & value) :
    name_(name), value_(value), next_(0)
{
    if (value_[0] == '\"' && value_[value_.size() - 1] == '\"') {
        value_.erase(value_.begin());
        value_.erase(value_.end() - 1);
    }
}

/**
 *  @details    Releases the resources used by the AttrNode object. Calling
 *              this destructor also destroys all nodes linked ahead by this
 *              node.
 */
AttrNode::~AttrNode()
{
    if (next_ != 0) {
        delete next_;
    }
}

/**
 *  @details    Get-method for the name member.
 *
 *  @return     A reference to the name member.
 */
const string & AttrNode::name() const
{
    return name_;
}

/**
 *  @details    Get-method for the name member.
 *
 *  @return     A reference to the name member.
 */
string & AttrNode::name()
{
    return name_;
}

/**
 *  @details    Get-method for the value member.
 *
 *  @return     A reference to the value member.
 */
const string & AttrNode::value() const
{
    return value_;
}

/**
 *  @details    Get-method for the value member.
 *
 *  @return     A reference to the value member.
 */
string & AttrNode::value()
{
    return value_;
}

/**
 *  @details    Get-method for the next member.
 *
 *  @return     A pointer to the next member.
 */
const AttrNode * AttrNode::next() const
{
    return next_;
}

/**
 *  @details    Get-method for the next member.
 *
 *  @return     A pointer to the next member.
 */
AttrNode * AttrNode::next()
{
    return next_;
}

/**
 *  @details    Set-method for the name member.
 *
 *  @param[in]  name                The new name.
 */
void AttrNode::setName(const string & name)
{
    name_ = name;
}

/**
 *  @details    Set-method for the value member.
 *
 *  @param[in]  value               The new value. It might be stripped of double-quotes.
 */
void AttrNode::setValue(const string & value)
{
    value_ = value;
    if (value_[0] == '\"' && value_[value_.size() - 1] == '\"') {
        value_.erase(value_.begin());
        value_.erase(value_.end() - 1);
    }
}

/**
 *  @details    Set-method for the next member.
 *
 *  @param[in]  nextNode            The value to set as the next link on the linked list.
 */
void AttrNode::setNext(AttrNode * nextNode)
{
    next_ = nextNode;
}

/**
 *  @details    Prints to stdout.
 */
void AttrNode::print() const
{
    cout << name_ << "=" << "\"" << value_ << "\" ";
}
