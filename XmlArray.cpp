/**
 *  @file   XmlArray.cpp
 *  @author Blurred-9L
 */

#include <stdexcept>
using std::out_of_range;

#include "XmlArray.h"


/**
 *  @details    Constructs a XmlArray object
 *
 *  @param[in]  objects             The array of XmlObjects
 *  @param[in]  size                The size of the array of XmlObjects
 */
XmlArray::XmlArray(XmlObject ** objects, int size) : XmlObject(), arrayData(objects), nObjects(size)
{
}

/**
 *  @details    Frees resources used by the XmlArray object. This includes deleting
 *              the elements on the array.
 */
XmlArray::~XmlArray()
{
    if (arrayData != 0) {
        for (int i = 0; i < nObjects; i++) {
            if (arrayData[i] != 0) {
                delete arrayData[i];
            }
        }
        delete [] arrayData;
    }
}

/**
 *  @details    Checks if the XmlObject is an array.
 *
 *  @return     Returns true.
 */
bool XmlArray::isArray() const
{
    return true;
}

/**
 *  @details    Gets the size of the array of XmlObjects.
 *
 *  @return     The number of objects on the array.
 */
int XmlArray::size() const
{
    return nObjects;
}

/**
 *  @details    Gets an element on the array. If the given index is not inside a the
 *              range [0, size), an out_of_range exception is thrown.
 *
 *  @param[in]  index               The index to access.
 *
 *  @return     A pointer to the XmlObject
 *
 *  @throw      std::out_of_range
 */
const XmlObject * XmlArray::get(int index) const
{
    if (index < 0 || index >= nObjects) throw std::out_of_range("Index out of range!");
    
    return arrayData[index];
}

/**
 *  @details    Gets an element on the array. If the given index is not inside a the
 *              range [0, size), an out_of_range exception is thrown.
 *
 *  @param[in]  index               The index to access.
 *
 *  @return     A pointer to the XmlObject
 *
 *  @throw      std::out_of_range
 */
XmlObject * XmlArray::get(int index)
{
    if (index < 0 || index >= nObjects) throw std::out_of_range("Index out of range!");
    
    return arrayData[index];
}
