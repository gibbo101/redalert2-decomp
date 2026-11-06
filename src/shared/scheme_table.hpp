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

#ifdef RA2_HASH_STRING_UNIT
// With HashString's member comparisons declared, the bucket vectors' element comparisons (VectorClass
// operator== 0x00605850 and the ID lookups) still call the free __fastcall ones (0x004E1290 / 0x004E12A0).
template <>
inline bool operator==(HashObject<HashString, SchemeNode *> const &a, HashObject<HashString, SchemeNode *> const &b)
{
    return ::operator==(a.Key, b.Key);
}
template <>
inline bool operator!=(HashObject<HashString, SchemeNode *> const &a, HashObject<HashString, SchemeNode *> const &b)
{
    return ::operator!=(a.Key, b.Key);
}
#endif

// Explicit specialization preserves the original typed layout and out-of-line lookup copies.
#ifdef RA2_HASH_STRING_UNIT
template <>
class HashTableClass<HashString, SchemeNode *> {
public:
    HashTableClass(int growth, int count, int (__fastcall *hash)(HashString const &key))
        : Hash(hash), BucketCount(count), GrowthStep(growth)
    {
        Buckets = new DynamicVectorClass<HashObject<HashString, SchemeNode *> >[count];
        for (int index = 0; index < BucketCount; index++) {
            Buckets[index].Set_Growth_Step(growth);
        }
    }
    ~HashTableClass() { delete[] Buckets; }

#ifdef RA2_MAP_HASH_ADD_SOURCE
    bool Add_Object(int bucket_index, HashObject<HashString, SchemeNode *> const &object); // original0056BC00
#endif

    // Files value under key unless the key's bucket already holds it.
    bool Add(HashString const &key, SchemeNode * const &value)
    {
        DynamicVectorClass<HashObject<HashString, SchemeNode *> > &bucket = Buckets[Hash(key) % BucketCount];
        bool found = false;
        for (int index = bucket.Count() - 1; index >= 0; index--) {
            if (bucket[index].Key.operator==(key)) {
                found = true;
                break;
            }
        }
        if (found)
            return false;
        return bucket.Add(HashObject<HashString, SchemeNode *>(key, value));
    }

    // The value filed under key, or null (the last match in its bucket).
    SchemeNode * *Find(HashString const &key);

    // The next non-empty key after the iterator's position, or null once past the last bucket.
    HashString *Next(UnknownSchemeListIterator &it);

    // Empties every bucket.
    void Clear()
    {
        for (int index = 0; index < BucketCount; index++) {
            Buckets[index].Clear();
        }
    }

    DynamicVectorClass<HashObject<HashString, SchemeNode *> > *Buckets;    // +0x00 BucketCount vectors
    int (__fastcall *Hash)(HashString const &key);               // +0x04
    int BucketCount;                                    // +0x08
    int GrowthStep;                                     // +0x0C
};
#endif

// The table's string hash (0x00603610): (c + hash * 26) % 31 over the text.
int __fastcall Unknown_Hash_00603610(HashString const &key);

class SchemeTable {
public:
    // 0x00604120 out of line (the destructor's lazy make calls it); expanded by every other lazy make.
    SchemeTable() : unknown_00(-1)
    {
        Names = new DynamicVectorClass<char *>;
        Colors = new DynamicVectorClass<HSVClass>;
        Table = new HashTableClass<HashString, SchemeNode *>(10, 31, Unknown_Hash_00603610);
    }
    ~SchemeTable();                                     // 0x00604250
    DynamicVectorClass<ColorScheme *> *Find_Schemes(char const *name);     // 0x006044A0 null when the palette has none
    // A new scheme list from the palette file name + the theater suffix + ".PAL" (null without a theater or
    // file; 0x00604540).
    DynamicVectorClass<ColorScheme *> *Build_Schemes(char const *name);
    // Files a node with a fresh list under the name (0x00604870).
    void Add_Node(char const *name);
    // Replaces the named node's list with a fresh one (0x006049C0).
    void Rebuild_Node(char const *name);
    // Stores the theater and rebuilds every node's list (0x00604AD0).
    void Set_Theater(int theater);

    int unknown_00;                                     // +0x00 (-1 when made; the theater)
    DynamicVectorClass<char *> *Names;                  // +0x04 the extra palette names (vtable 0x0079E55C)
    DynamicVectorClass<HSVClass> *Colors;               // +0x08 their colours (vtable 0x007A7B58)
    HashTableClass<HashString, SchemeNode *> *Table;    // +0x0C 31 buckets, growth 10
};

extern SchemeTable *unknown_scheme_table_a76414;        // 0x00A76414

// The table, made on first use.
inline SchemeTable *Scheme_Table()
{
    if (unknown_scheme_table_a76414 == 0) {
        unknown_scheme_table_a76414 = new SchemeTable;
    }
    return unknown_scheme_table_a76414;
}

void Unknown_00603FA0();                                // 0x00603FA0 deletes the table (Prog_End)

#endif
