/**
 *  @file   XmlSyntaxError.cpp
 *  @author Blurred-9L
 */

#include "XmlSyntaxError.h"

/**
 *  @details    Constructs a XmlSyntaxError object.
 */
XmlSyntaxError::XmlSyntaxError() :
    runtime_error("Syntax Error during XML parsing!")
{
}
