/**
 *  @file   XmlWrapper.h
 *  @author Blurred-9L
 */

#include <stdexcept>
using std::runtime_error;

#include "XmlArray.h"
#include "XmlDictionary.h"
#include "XmlObject.h"
#include "XmlValue.h"
#include "XmlWrapper.h"

/**
 *  @details    Constructs a XmlWrapper object.
 *
 *  @param[in]  object              The XmlObject wrapped by this object.
 */
XmlWrapper::XmlWrapper(XmlObject & object) : object(object)
{
}

/**
 *  @details    Overloads the [] operator in order to provide easy access
 *              to the content of an XmlArray object. If the wrapped object
 *              is not a XmlArray, an exception is thrown.
 *
 *  @param[in]  index               The index to access.
 *
 *  @return     A XmlWrapper which wraps the object at the given index.
 *
 *  @throw      std::runtime_error
 *  @throw      std::out_of_range
 */
XmlWrapper XmlWrapper::operator[](int index) const
{
    if (!object.isArray()) throw runtime_error("XmlObject is not XmlArray!");
    
    return *dynamic_cast<XmlArray *>(&object)->get(index);
}

/**
 *  @details    Overloads the [] operator in order to provide easy access
 *              to the content of an XmlDictionary object. If the wrapped object
 *              is not a XmlDictionary, an exception is thrown.
 *
 *  @param[in]  key                 The key from which to access the mapped object.
 *
 *  @return     A XmlWrapper which wraps the object related to the given key
 *
 *  @throw      std::runtime_error
 *  @throw      XmlNoKeyFound
 */
XmlWrapper XmlWrapper::operator[](const string & key) const
{
    if (!object.isDictionary()) throw runtime_error("XmlObject is not XmlDictionary!");
    
    return *dynamic_cast<XmlDictionary *>(&object)->get(key);
}

/**
 *  @details    Gets the contents of a leaf node. If the wrapped object is not a
 *              XmlValue, an exception is thrown.
 *
 *  @return     A reference to the contents of the TagNode.
 *
 *  @throw      std::runtime_error
 */
const string & XmlWrapper::get() const
{
    if (!object.isValue()) throw runtime_error("XmlObject is not XmlValue!");
    
    return dynamic_cast<XmlValue *>(&object)->content();
}

/**
 *  @details    Gets the contents of a leaf node. If the wrapped object is not a
 *              XmlValue, an exception is thrown.
 *
 *  @return     A reference to the contents of the TagNode.
 *
 *  @throw      std::runtime_error
 */
string & XmlWrapper::get()
{
    if (!object.isValue()) throw runtime_error("XmlObject is not XmlValue!");
    
    return dynamic_cast<XmlValue *>(&object)->content();
}

/**
 *  @details    Gets the size of the wrapped object if it is an XmlArray, otherwise
 *              an exception is thrown.
 *
 *  @return     The size of the XmlArray
 *
 *  @throw      std::runtime_error
 */
int XmlWrapper::size() const
{
    if (!object.isArray()) throw runtime_error("XmlObject has no size!");
    
    return dynamic_cast<XmlArray *>(&object)->size();
    
}

/**
 *  @details    Gets the size of the wrapped object if it is an XmlDictionary, otherwise
 *              an exception is thrown.
 *
 *  @return     The size of the XmlDictionary
 *
 *  @throw      std::runtime_error
 */
int XmlWrapper::numEntries() const
{
    if (!object.isDictionary()) throw runtime_error("XmlObject has no keys!");
    
    return dynamic_cast<XmlDictionary *>(&object)->size();
}
