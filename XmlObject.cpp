#include "XmlObject.h"

/**
 *  @details    Constructs a XmlObject
 */
XmlObject::XmlObject()
{
}

/**
 *  @details    Destroys a XmlObject
 */
XmlObject::~XmlObject()
{
}

/**
 *  @details    Checks if the XmlObject is a mixed dictionary.
 *
 *  @return     Returns false
 */
bool XmlObject::isMixedDictionary() const
{
    return false;
}

/**
 *  @details    Checks if the XmlObject is a dictionary.
 *
 *  @return     Returns false
 *
 *  @sa         XmlDictionary::isDictionary()
 */
bool XmlObject::isDictionary() const
{
    return false;
}

/**
 *  @details    Checks if the XmlObject is an array.
 *
 *  @return     Returns false
 *
 *  @sa         XmlArray::isArray()
 */
bool XmlObject::isArray() const
{
    return false;
}

/**
 *  @details    Checks if the XmlValue is a single value.
 *
 *  @return     Returns false
 *
 *  @sa         XmlValue::isValue()
 */
bool XmlObject::isValue() const
{
    return false;
}
