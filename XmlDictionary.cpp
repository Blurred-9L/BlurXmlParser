/**
 *  @file   XmlDictionary.cpp
 *  @author Blurred-9L
 */

#include "XmlNoKeyFound.h"

#include "XmlDictionary.h"

/**
 *  @details    Constructs an empty XmlDictionary
 */
XmlDictionary::XmlDictionary() : XmlObject(), HashTable<string, XmlObject *, StringHasher>(),
    hashTable(0), nElements(0)
{
    hashTable = new list<KeyValuePair<string, XmlObject *> *> [NUM_BUCKETS];
}

/**
 *  @details    Releases the resources used by the XmlDictionary. This also releases
 *              the resources used by the stored XmlObjects.
 */
XmlDictionary::~XmlDictionary()
{
    
    if (hashTable != 0) {
        clear();
        delete [] hashTable;
    }
}

/**
 *  @details    Checks if the XmlObject is a XmlDictionary
 *
 *  @return     Returns true
 */
bool XmlDictionary::isDictionary() const
{
    return true;
}

/**
 *  @details    Empties the contents of the XmlDictionary, deleting the
 *              contained XmlObjects as well.
 */
void XmlDictionary::clear()
{
    for (int i = 0; i < NUM_BUCKETS; i++) {
        while (!hashTable[i].empty()) {
            delete hashTable[i].front()->value();
            delete hashTable[i].front();
            hashTable[i].pop_front();
        }
    }
    nElements = 0;
}

/**
 *  @details    Gets the number of key-value pairs stored in the XmlDictionary
 *
 *  @return     The size of the dictionary.
 */
int XmlDictionary::size() const
{
    return nElements;
}

/**
 *  @details    Adds a new entry to the XmlDictionary. The current implementation of
 *              the XmlDictionary does not allow repeated keys, however, a key can
 *              be mapped to an XmlArray in order to bypass this limitation.
 *
 *  @param[in]  key                 The key of the pair to add.
 *  @param[in]  value               The value of the pair to add.
 *
 *  @return     Returns a boolean value indicating if the operation was successful.
 */
bool XmlDictionary::add(const string & key, XmlObject * const & value)
{
    StringHasher hasher;
    bool ok = false;
    int hashKey;
    
    if (!has_key(key)) {
        hashKey = hasher.hash(key) % NUM_BUCKETS;
        hashTable[hashKey].push_back(new KeyValuePair<string, XmlObject *>(key, const_cast<XmlObject *>(value)));
        nElements++;
        ok = true;
    }
    
    return ok;
}

/**
 *  @details    Tries to get the value mapped to the given key. If the key is not stored
 *              inside this dictionary, an exception is thrown.
 *
 *  @param[in]  key                 The key of the value to look for.
 *
 *  @return     A reference to a pointer of the stored XmlObject.
 *
 *  @throw      XmlNoKeyFound
 */
XmlObject * const & XmlDictionary::get(const string & key) const
{
    list<KeyValuePair<string, XmlObject *> *>::const_iterator i, it;
    StringHasher hasher;
    int hashKey;
    bool found = false;
    
    hashKey = hasher.hash(key) % NUM_BUCKETS;
    if (hashTable[hashKey].size() > 0) {
        for (i = hashTable[hashKey].begin(); i != hashTable[hashKey].end() && !found; ++i) {
            if ((*i)->key() == key) {
                it = i;
                found = true;
            }
        } 
    }
    if (!found) { throw XmlNoKeyFound(key); }
    
    return (*it)->value();
}

/**
 *  @details    Tries to get the value mapped to the given key. If the key is not stored
 *              inside this dictionary, an exception is thrown.
 *
 *  @param[in]  key                 The key of the value to look for.
 *
 *  @return     A reference to a pointer of the stored XmlObject.
 *
 *  @throw      XmlNoKeyFound
 */
XmlObject * & XmlDictionary::get(const string & key)
{
    list<KeyValuePair<string, XmlObject *> *>::iterator i, it;
    StringHasher hasher;
    int hashKey;
    bool found = false;
    
    hashKey = hasher.hash(key) % NUM_BUCKETS;
    if (hashTable[hashKey].size() > 0) {
        for (i = hashTable[hashKey].begin(); i != hashTable[hashKey].end() && !found; ++i) {
            if ((*i)->key() == key) {
                it = i;
                found = true;
            }
        } 
    }
    if (!found) throw XmlNoKeyFound(key);
    
    return (*it)->value();
}

/**
 *  @details    Tries to remove the element mapped to the given key.
 *
 *  @param[in]  key                 The key of the element to remove.
 *
 *  @return     Returns a boolean value indicating the success of the operation.
 */
bool XmlDictionary::remove(const string & key)
{
    list<KeyValuePair<string, XmlObject *> *>::iterator i, it;
    StringHasher hasher;
    int hashKey;
    bool found = false;
    
    hashKey = hasher.hash(key) % NUM_BUCKETS;
    if (hashTable[hashKey].size() > 1) {
        for (i = hashTable[hashKey].begin(); i != hashTable[hashKey].end() && !found; ++i) {
            if ((*i)->key() == key) {
                it = i;
                found = true;
            }
        } 
    }
    if (found) {
        delete (*i)->value();
        delete *i;
        hashTable[hashKey].erase(it);
        nElements--;
    }
    
    return found;
}

/**
 *  @details    Checks if the given key is stored inside this dictionary.
 *
 *  @param[in]  key                 The key to look for.
 *
 *  @return     Returns a boolean value indicating if the dictionary contains the given
 *              key.
 */
bool XmlDictionary::has_key(const string & key) const
{
    list<KeyValuePair<string, XmlObject *> *>::iterator i;
    StringHasher hasher;
    int hashKey;
    bool found = false;
    
    hashKey = hasher.hash(key) % NUM_BUCKETS;
    if (hashTable[hashKey].size() > 1) {
        for (i = hashTable[hashKey].begin(); i != hashTable[hashKey].end() && !found; ++i) {
            if ((*i)->key() == key) {
                found = true;
            }
        } 
    }
    
    return found;
}
