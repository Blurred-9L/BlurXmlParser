/**
 *  @file   XmlDictionary.h
 *  @author Blurred-9L
 */

#ifndef XML_PARSER_XML_DICTIONARY_H
#define XML_PARSER_XML_DICTIONARY_H

#include <list>
using std::list;

#include "BlurDataStructures/Base/HashTable.h"
#include "BlurDataStructures/Utility/KeyValuePair.h"

#include "StringHasher.h"
#include "XmlObject.h"

#define NUM_BUCKETS 7

/**
 *  @class  XmlDictionary
 *
 *  @brief  Inherits from XmlObject to represent a tag and its children on the
 *          xml document. This class implements the HashTable interface using
 *          strings as keys, pointers to XmlObjects as values and a StringHasher
 *          as the hash function.
 */
class XmlDictionary : public XmlObject, public HashTable<string, XmlObject *, StringHasher> {
private:
    /// The array of buckets for the hash table
    list<KeyValuePair<string, XmlObject *> *> * hashTable;
    /// The number of elements
    int nElements;
    
public:
    /// Constructor
    XmlDictionary();
    /// Destructor
    virtual ~XmlDictionary();
    /// Checks if XmlObject is XmlDictionary
    bool isDictionary() const;
    /// Clears dictionary contents
    void clear();
    /// Gets the number of elements stored
    int size() const;
    /// Adds key-value pair to dictionary
    bool add(const string & key, XmlObject * const & value);
    /// Gets the value related to key
    XmlObject * const & get(const string & key) const;
    /// Gets the value related to key
    XmlObject * & get(const string & key);
    /// Removes the value related to key
    bool remove(const string & key);
    /// Checks if key exists
    bool has_key(const string & key) const;
};

#endif /// NOT XML_PARSER_XML_DICTIONARY_H
