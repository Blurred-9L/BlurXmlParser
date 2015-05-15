/**
 *  @file   XmlWrapper.h
 *  @author Blurred-9L
 */

#ifndef XML_WRAPPER_H
#define XML_WRAPPER_H

#include <string>
using std::string;

class XmlObject;

/**
 *  @class  XmlWrapper
 *
 *  @brief  Class that wraps overs an XmlObject to further simplify the access
 *          to the values at the leaf nodes.
 */
class XmlWrapper {
private:
    /// The object being wrapped
    XmlObject & object;
    
public:
    /// Constructor
    XmlWrapper(XmlObject & object);
    /// Gets value if object is array
    XmlWrapper operator[](int index) const;
    /// Gets value if object is dictionary
    XmlWrapper operator[](const string & key) const;
    /// Gets content if object is value
    const string & get() const;
    /// Gets content if object is value
    string & get();
    /// Gets size of array if object is array
    int size() const;
    /// Gets size of dictionary if object is dictionary
    int numEntries() const;
};

#endif /// NOT XML_WRAPPER_H
