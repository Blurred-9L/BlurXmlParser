/**
 *  @file   XmlOutOfTokens.cpp
 *  @author Blurred-9L
 */

#include "XmlOutOfTokens.h"

/**
 *  @details    Constructs a XmlOutOfTokens object.
 */
XmlOutOfTokens::XmlOutOfTokens() :
    runtime_error("Ran out of tokens during parsing!")
{
}
