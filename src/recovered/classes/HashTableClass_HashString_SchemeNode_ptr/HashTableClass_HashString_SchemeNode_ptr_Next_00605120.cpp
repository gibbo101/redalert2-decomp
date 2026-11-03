#include "shared/scheme_table.hpp"
HashString *HashTableClass<HashString, SchemeNode *>::Next(UnknownSchemeListIterator &it)
{
        if (it.Done) {
            return 0;
        }
        while (it.Bucket < BucketCount) {
            DynamicVectorClass<HashObject<HashString, SchemeNode *> > &bucket = Buckets[it.Bucket];
            while (it.Index < bucket.Count()) {
                HashObject<HashString, SchemeNode *> &object = bucket[it.Index];
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
