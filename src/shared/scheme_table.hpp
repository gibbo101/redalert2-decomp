// The per-palette colour-scheme table (0x00A76414, made on first use): palette file names mapped to the
// SchemeNode lists built for that palette (the scheme unit 0x00603200-0x00604CC0 after palette.cpp; RA2 only).
// The table's layout is from its constructor 0x00604120; names are hypotheses. Included after the unit's
// SchemeNode definition (0x00603200 source); the unit defines RA2_HASH_STRING_UNIT (HashString's member
// constructor, Is_Empty and operator== are called).
#ifndef RA2_SHARED_SCHEME_TABLE_HPP
#define RA2_SHARED_SCHEME_TABLE_HPP

#include "shared/hash_string.hpp"
#include "shared/color_scheme.hpp"
#include "shared/hash_table.hpp"

class SchemeNode;

class SchemeTable {
public:
    SchemeTable();                                      // 0x00604120
    ~SchemeTable();                                     // 0x00604250
    DynamicVectorClass<ColorScheme *> *Find_Schemes(char const *name);     // 0x006044A0 null when the palette has none

    int unknown_00;                                     // +0x00 (-1 when made; the theater of 0x00603750)
    void *unknown_04;                                   // +0x04 a DynamicVectorClass (vtable 0x0079E55C)
    void *unknown_08;                                   // +0x08 a DynamicVectorClass (vtable 0x007A7B58)
    HashTableClass<HashString, SchemeNode *> *Table;    // +0x0C 31 buckets, growth 10, hash 0x00603610
};

extern SchemeTable *unknown_scheme_table_a76414;        // 0x00A76414

void Unknown_00603FA0();                                // 0x00603FA0 deletes the table (Prog_End)

#endif
