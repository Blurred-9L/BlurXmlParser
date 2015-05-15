/**
 *  @file   XmlValue.cpp
 *  @author Blurred-9L
 */

#include "TagNode.h"

#include "XmlValue.h"

/**
 *  @details    Constructs a XmlValue object
 *
 *  @param[in]  tag                 The encapsulated tag.
 */
XmlValue::XmlValue(TagNode * tag) : XmlObject(), tag(tag)
{
}

/**
 *  @details    Destroys a XmlValue
 */
XmlValue::~XmlValue()
{
}

/**
 *  @details    Checks if XmlObject is a single value.
 *
 *  @return     Returns true
 */
bool XmlValue::isValue() const
{
    return true;
}

/**
 *  @details    Gets the contents of the encapsulated tag.
 *
 *  @return     A reference to the tag's contents.
 */
const string & XmlValue::content() const
{
    return tag->contents();
}

/**
 *  @details    Gets the contents of the encapsulated tag.
 *
 *  @return     A reference to the tag's contents.
 */
string & XmlValue::content()
{
    return tag->contents();
}
