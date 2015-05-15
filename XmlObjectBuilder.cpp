/**
 *  @file   XmlObjectBuilder.cpp
 *  @author Blurred-9L
 */

#include <set>
using std::set;

#include "XmlArray.h"
#include "XmlDictionary.h"
#include "XmlObject.h"
#include "XmlValue.h"

#include "XmlObjectBuilder.h"

using std::pair;
using std::make_pair;

/**
 *  @details    Constructs a XmlObjectBuilder.
 */
XmlObjectBuilder::XmlObjectBuilder() : data(), allDifferent(true), allEqual(false), repeatedKeys(false)
{
}

/**
 *  @details    Adds a new key-value pair to the internal storage structure. In order to know which
 *              object will be instantiated upon requests, the internal flags indicating if the keys
 *              are different, equal or if there are repeated keys will be modified depending on the
 *              key for the new pair.
 *
 *  @param[in]  key                 The key of the pair to add.
 *  @param[in]  object              The mapped object of the pair to add.
 */
void XmlObjectBuilder::add(const string & key, XmlObject * object)
{
    int elemCount = data.size();
    int keyCount;
    
    
    if (elemCount > 0) {
        keyCount = data.count(key);
        if (allDifferent) {
            if (keyCount > 0) {
                allDifferent = false;
                repeatedKeys = true;
                if (keyCount == elemCount) {
                    allEqual = true;
                }
            }
        } else if (allEqual) {
            if (keyCount == 0) {
                allEqual = false;
            }
        }
    }
    data.insert(make_pair(key, object));
}

/**
 *  @details    Resets the state of the XmlObjectBuilder to default so
 *              that it might be used again.
 */
void XmlObjectBuilder::reset()
{
    data.clear();
    allDifferent = true;
    allEqual = false;
    repeatedKeys = false;
}

/**
 *  @details    Constructs and returns the XmlObject with all the given pairs up
 *              until the call to this method.
 *
 *  @return     If all the keys given were different, a XmlDictionary is returned.
 *              If all the keys given were equal, then a XmlArray is returned. If
 *              there was a mixture of both unique and repeated keys, then a
 *              XmlDictionary is returned, with the repeated keys added to the dictionary
 *              as a XmlArray.
 */
XmlObject * XmlObjectBuilder::getXmlObject()
{
    XmlObject * object = 0;
    
    if (allDifferent) {
        object = buildXmlDictionary();
    } else if (allEqual) {
        object = buildXmlArray();
    } else {
        object = buildMixedDictionary();
    }
    
    return object;
}

/////////////
// Private //
/////////////

/**
 *  @details    Builds a XmlArray with the given keys and values
 *              contained on the XmlObjectBuilder.
 *
 *  @return     The pointer to the recently created XmlArray.
 */
XmlArray * XmlObjectBuilder::buildXmlArray()
{
    XmlArray * array = 0;
    int size = data.size();
    XmlObject ** objectArray = new XmlObject * [size];
    multimap<string, XmlObject *>::iterator i;
    int index = 0;
    
    for (i = data.begin(); i != data.end(); ++i) {
        objectArray[index++] = i->second;
    }
    array = new XmlArray(objectArray, size);
    
    return array;
}

/**
 *  @details    Builds a XmlDictionary with the given keys and values
 *              contained on the XmlObjectBuilder.
 *
 *  @return     The pointer to the recently created XmlDictionary.
 */
XmlDictionary * XmlObjectBuilder::buildXmlDictionary()
{
    XmlDictionary * dictionary = new XmlDictionary;
    multimap<string, XmlObject *>::iterator i;
    
    for (i = data.begin(); i != data.end(); ++i) {
        dictionary->add(i->first, i->second);
    }
    
    return dictionary;
}

/**
 *  @details    Builds a XmlDictionary, however key-value pairs with the
 *              same keys are grouped into a XmlArray before being added
 *              to the XmlDictionary.
 *
 *  @return     The pointer to the recently created XmlDictionary.
 */
XmlDictionary * XmlObjectBuilder::buildMixedDictionary()
{
    typedef multimap<string, XmlObject *>::iterator multimap_iterator;
    XmlDictionary * dictionary = new XmlDictionary;
    multimap<string, XmlObject *>::iterator i;
    set<string> keySet;
    set<string>::iterator j;
    int keyCount, index;
    
    for (i = data.begin(); i != data.end(); ++i) {
        keySet.insert(i->first);
    }
    for (j = keySet.begin(); j != keySet.end(); ++j) {
        keyCount = data.count(*j);
        if (keyCount == 1) {
            dictionary->add(*j, data.find(*j)->second);
        } else {
            pair<multimap_iterator, multimap_iterator> range = data.equal_range(*j);
            XmlObject ** objectArray = new XmlObject * [keyCount];
            index = 0;
            for (i = range.first; i != range.second; ++i) {
                objectArray[index++] = i->second;
            }
            dictionary->add(*j, new XmlArray(objectArray, keyCount));
        }
    }
    
    return dictionary;
}
