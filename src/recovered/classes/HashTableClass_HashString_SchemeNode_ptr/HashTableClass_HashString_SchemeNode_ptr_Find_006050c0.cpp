#include "shared/scheme_table.hpp"
SchemeNode **HashTableClass<HashString, SchemeNode *>::Find(HashString const &key)
{
        DynamicVectorClass<HashObject<HashString, SchemeNode *> > &bucket = Buckets[Hash(key) % BucketCount];
        for (int index = bucket.Count() - 1; index >= 0; index--) {
            HashObject<HashString, SchemeNode *> &object = bucket[index];
            if (object.Key.operator==(key)) {
                return &object.Value;
            }
        }
        return 0;
    }
