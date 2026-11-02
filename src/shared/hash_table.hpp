// HashTableClass<K, V>: Westwood's chained hash table (Tiberian Sun hashtable.h: the constructor's
// (growth, count, hash) argument order, the bucket array of DynamicVectorClass<HashObject<K, V> >, the
// hash function, the bucket count and the growth step). Instances: the map's subzone tables
// (shared/map.hpp, 256 buckets, growth 20, hash 0x0054F240), the radar's tracking table (shared/radar.hpp,
// hash 0x00631C60) and the colour-scheme table (shared/scheme_table.hpp, 31 buckets, growth 10, hash
// 0x00603610). The scheme table's Find (0x006050C0), Next (0x00605120) and constructor (0x00605020) are
// out of line where a caller's inline budget runs out; Add, Clear and the destructor only expand inline.
// The hash returns int: the scheme table's bucket index is a signed remainder (cdq; idiv).
#ifndef RA2_SHARED_HASH_TABLE_HPP
#define RA2_SHARED_HASH_TABLE_HPP

#include "shared/hash_object.hpp"
#include "shared/vector_class.hpp"

struct UnknownSchemeListIterator;

template <class K, class V>
class HashTableClass {
public:
    HashTableClass(int growth, int count, int (__fastcall *hash)(K const &key))
        : Hash(hash), BucketCount(count), GrowthStep(growth)
    {
        Buckets = new DynamicVectorClass<HashObject<K, V> >[count];
        for (int index = 0; index < BucketCount; index++) {
            Buckets[index].Set_Growth_Step(growth);
        }
    }
    ~HashTableClass() { delete[] Buckets; }

#ifdef RA2_MAP_HASH_ADD_SOURCE
    bool Add_Object(int bucket_index, HashObject<K, V> const &object); // original0056BC00
#endif

    // Files value under key unless the key's bucket already holds it.
    bool Add(K const &key, V const &value)
    {
        DynamicVectorClass<HashObject<K, V> > &bucket = Buckets[Hash(key) % BucketCount];
        for (int index = bucket.Count() - 1; index >= 0; index--) {
            if (bucket[index].Key.operator==(key)) {
                return false;
            }
        }
        return bucket.Add(HashObject<K, V>(key, value));
    }

    // The value filed under key, or null (the last match in its bucket).
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

    // The next non-empty key after the iterator's position, or null once past the last bucket.
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
            it.Bucket++;
            it.Index = 0;
        }
        it.Done = true;
        return 0;
    }

    // Empties every bucket.
    void Clear()
    {
        for (int index = 0; index < BucketCount; index++) {
            Buckets[index].Clear();
        }
    }

    DynamicVectorClass<HashObject<K, V> > *Buckets;    // +0x00 BucketCount vectors
    int (__fastcall *Hash)(K const &key);               // +0x04
    int BucketCount;                                    // +0x08
    int GrowthStep;                                     // +0x0C
};

#endif
