/**
 *  @file   XmlNestingError.h
 *  @author Blurred-9L
 */

#ifndef XML_PARSER_XML_NESTING_ERROR_H
#define XML_PARSER_XML_NESTING_ERROR_H

#include <stdexcept>
using std::runtime_error;

/**
 *  @class  XmlNestingError
 *
 *  @brief  Exception used when a nesting error is found during xml parsing.
 */
class XmlNestingError : public std::runtime_error {
public:
    /// Constructor
    XmlNestingError();
};

#endif /// NOT XML_PARSER_XML_NESTING_ERROR_H
