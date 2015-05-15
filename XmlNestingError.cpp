/**
 *  @file   XmlNestingError.cpp
 *  @author Blurred-9L
 */

#include "XmlNestingError.h"

/**
 *  @details    Constructs a XmlNestingError.
 */
XmlNestingError::XmlNestingError() :
    runtime_error("Incorrectly nested tags found!")
{
}
