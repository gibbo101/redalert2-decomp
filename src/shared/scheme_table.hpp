// The per-palette colour-scheme table (0x00A76414, made on first use): palette file names mapped to the
// SchemeNode lists built for that palette (the scheme unit 0x00603200-0x00604CC0 after palette.cpp; RA2 only).
// The table's layout is from its constructor 0x00604120; names are hypotheses. Included after the unit's
// SchemeNode definition (0x00603200 source); the unit defines RA2_HASH_STRING_UNIT (HashString's member
// constructor, Is_Empty and operator== are called).
#ifndef RA2_SHARED_SCHEME_TABLE_HPP
#define RA2_SHARED_SCHEME_TABLE_HPP

#include "shared/hash_string.hpp"
#include "shared/color_scheme.hpp"

class SchemeNode;

// Westwood's chained hash table (Tiberian Sun hashtable.h order of the constructor's arguments; shared/map.hpp
// declares the map's instances with the same layout).
template <class K, class V>
class HashTableClass {
public:
    HashTableClass(int growth, int count, int (__fastcall *hash)(K const &key));   // 0x00605020 for <HashString, SchemeNode *>

    // The value filed under key, or null (the last match in its bucket; 0x006050C0 out of line).
    V *Find(K const &key)
    {
        DynamicVectorClass<HashObject<K, V> > &bucket = Buckets[Hash(key) % BucketCount];
        for (int index = bucket.Count() - 1; index >= 0; index--) {
            HashObject<K, V> &object = bucket[index];
            if (object.Key.operator==(key)) {
                return &object.Value;
            }
        }
        return 0;
    }

    // The next non-empty key after the iterator's position, or null once past the last bucket (0x00605120
    // out of line).
    K *Next(UnknownSchemeListIterator &it)
    {
        if (it.Done) {
            return 0;
        }
        while (it.Bucket < BucketCount) {
            DynamicVectorClass<HashObject<K, V> > &bucket = Buckets[it.Bucket];
            while (it.Index < bucket.Count()) {
                HashObject<K, V> &object = bucket[it.Index];
                it.Index++;
                if (!object.Key.Is_Empty()) {
                    return &object.Key;
                }
            }
            it.Index = 0;
            it.Bucket++;
        }
        it.Done = true;
        return 0;
    }

    DynamicVectorClass<HashObject<K, V> > *Buckets;    // +0x00 BucketCount vectors
    int (__fastcall *Hash)(K const &key);               // +0x04
    int BucketCount;                                    // +0x08
    int GrowthStep;                                     // +0x0C
};

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
