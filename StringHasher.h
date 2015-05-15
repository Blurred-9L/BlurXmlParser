/**
 *  @file   StringHasher.h
 *  @author Blurred-9L
 */

#ifndef XML_PARSER_STRING_HASHER_H
#define XML_PARSER_STRING_HASHER_H

#include <string>
using std::string;

/**
 *  @class  StringHasher
 *
 *  @brief  Class used to perform a hash operation on a string.
 */
class StringHasher {
public:
    /// Hashes key
    int hash(const string & key);
};

#endif /// NOT XML_PARSER_STRING_HASHER_H
