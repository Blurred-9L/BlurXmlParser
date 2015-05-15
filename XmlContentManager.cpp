/**
 *  @file   XmlContentManager.cpp
 *  @author Blurred-9L
 */

#include "XmlContentManager.h"

/**
 *  @details    Constructs a XmlContentManager object by opening a file
 *              and then passing its contents to memory.
 *
 *  @param[in]  filename            A c-style string. The file to open.
 */
XmlContentManager::XmlContentManager(const char * filename)
{
    ifstream file(filename);
    string line;
    
    if (file.is_open()) {
        getline(file, line);
        while (!file.eof()) {
            lines.push_back(line);
            getline(file, line);
        }
        file.close();
    }
}

/**
 *  @details    Gets a line from the xml file.
 *
 *  @param[in]  index               The zero-based index of the line to use.
 *
 *  @return     A string with the line requested.
 *
 *  @throw      std::out_of_range
 */
string & XmlContentManager::getLine(int index)
{
    return lines[index];
}

/**
 *  @details    Gets a line from the xml file.
 *
 *  @param[in]  index               The zero-based index of the line to use.
 *
 *  @return     A string with the line requested.
 *
 *  @throw      std::out_of_range
 */
const string & XmlContentManager::getLine(int index) const
{
    return lines[index];
}
