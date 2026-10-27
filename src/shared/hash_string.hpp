// HashString: the 256-byte key buffer of the color scheme table's HashObject elements
// (HashObject<HashString, SchemeNode *>, 0x104 bytes; the hash table of ColorScheme.cpp).
// The copy and comparison are out of line in the original (0x004E1180 copies the string
// by strlen and rep movs; 0x004E1290 / 0x004E12A0 are __fastcall comparisons); only
// their declarations are known. Names and layout are hypotheses.
#ifndef RA2_SHARED_HASH_STRING_HPP
#define RA2_SHARED_HASH_STRING_HPP

#include "shared/hash_object.hpp"

class SchemeNode;

class HashString {
public:
    HashString();                                       // 0x004E1130
    HashString(HashString const &other);                // 0x004E1180
    HashString &operator=(HashString const &other);     // 0x004E11C0
    char Text[0x100];
};
bool __fastcall operator==(HashString const &a, HashString const &b);   // 0x004E1290
bool __fastcall operator!=(HashString const &a, HashString const &b);   // 0x004E12A0

#endif
