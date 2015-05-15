/**
 *  @file   XmlSyntaxError.h
 *  @author Blurred-9L
 */

#ifndef XML_PARSER_XML_SYNTAX_ERROR_H
#define XML_PARSER_XML_SYNTAX_ERROR_H

#include <stdexcept>
using std::runtime_error;

/**
 *  @class  XmlSyntaxError
 *
 *  @brief  Exception used whenever a syntax error happens during xml parsing.
 */
class XmlSyntaxError : public runtime_error {
public:
    /// Constructor
    XmlSyntaxError();
};

#endif /// NOT XML_PARSER_XML_SYNTAX_ERROR_H
