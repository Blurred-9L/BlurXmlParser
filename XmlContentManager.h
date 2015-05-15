/**
 *  @file   XmlContentManager.h
 *  @author Blurred-9L
 */

#ifndef XML_PARSER_XML_CONTENT_MANAGER_H
#define XML_PARSER_XML_CONTENT_MANAGER_H

#include <fstream>
using std::ifstream;
#include <string>
using std::string;
#include <vector>
using std::vector;

/**
 *  @class  XmlContentManager
 *
 *  @brief  The XmlContentManager holds the plain-text data found on an xml
 *          file and can be used to access it.
 */
class XmlContentManager {
private:
    /// The lines in the file
    vector<string> lines;

public:
    /// Constructor
    explicit XmlContentManager(const char * filename);
    /// Gets a line
    string & getLine(int index);
    /// Gets a line
    const string & getLine(int index) const;
};

#endif /// NOT XML_PARSER_XML_CONTENT_MANAGER_H
