/**
 *  @file   XmlNoKeyFound.h
 *  @author Blurred-9L
 */

#ifndef XML_PARSER_XML_NO_KEY_FOUND_H
#define XML_PARSER_XML_NO_KEY_FOUND_H

#include <stdexcept>
using std::out_of_range;
#include <string>
using std::string;

/**
 *  @class  XmlNoKeyFound
 *
 *  @brief  Exception used when access is made through a key that does not exist.
 */
class XmlNoKeyFound : public out_of_range {
public:
    /// Constructor
    explicit XmlNoKeyFound(const string & keyUsed);
};

#endif /// NOT XML_PARSER_XML_NO_KEY_FOUND_H
