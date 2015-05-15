/**
 *  @file   XmlOutOfTokens.h
 *  @author Blurred-9L
 */

#ifndef XML_PARSER_XML_OUT_OF_TOKENS_H
#define XML_PARSER_XML_OUT_OF_TOKENS_H

#include <stdexcept>
using std::runtime_error;

/**
 *  @class  XmlOutOfTokens
 *
 *  @brief  Exception used when parsing of an xml document continues but no
 *          more tokens are available.
 */
class XmlOutOfTokens : public runtime_error {
public:
    /// Constructor
    XmlOutOfTokens();
};

#endif /// NOT XML_PARSER_XML_OUT_OF_TOKENS_H
