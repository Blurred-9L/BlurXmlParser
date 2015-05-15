/**
 *  @file   StringHasher.cpp
 *  @author Blurred-9L
 */

#include "StringHasher.h"

/**
 *  @details    Creates a hash value from the given key by using a
 *              a PJW hash function. The value obtained is not limited
 *              by any modulo operation, this should be done from the
 *              place this method is called.
 *
 *  @param[in]  key                 The key to hash
 *
 *  @return     The result of hash(key), that is, the result of applying a hash
 *              function to the given key.
 */
int StringHasher::hash(const string & key)
{
    int i, size = key.size();
    unsigned h = 0, g;
    
    for (i = 0; i < size; i++) {
        h = (h << 4) + key[i];
        g = h & 0xF0000000;
        if (g > 1) {
            h = h ^ (g << 24);
            h = h ^ g;
        }
    }
    
    return h;
}
