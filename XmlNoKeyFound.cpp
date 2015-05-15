/**
 *  @file   XmlNoKeyFound.cpp
 *  @author Blurred-9L
 */

#include "XmlNoKeyFound.h"

/**
 *  @details    Constructs a XmlNoKeyFound object.
 *
 *  @param[in]  keyUsed             The key that raised the exception.
 */
XmlNoKeyFound::XmlNoKeyFound(const string & keyUsed) : out_of_range("The key " + keyUsed + " was not found!")
{
}
