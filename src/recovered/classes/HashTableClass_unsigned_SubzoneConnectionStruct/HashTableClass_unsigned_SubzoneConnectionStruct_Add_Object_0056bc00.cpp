// HashTableClass<unsigned int, SubzoneConnectionStruct>::Add_Object0056BC00.
#include "shared/map.hpp"
template <> bool HashTableClass<unsigned int, SubzoneConnectionStruct>::Add_Object(int bucket_index, HashObject<unsigned int, SubzoneConnectionStruct> const &object)
{
    DynamicVectorClass<HashObject<unsigned int, SubzoneConnectionStruct> > &bucket = Buckets[bucket_index];
    HashObject<unsigned int, SubzoneConnectionStruct> *item = &bucket[0];
    for (int remaining = bucket.Count() - 1; remaining >= 0; --remaining) {
        if (object.Key == item->Key) return false;
        ++item;
    }
    bucket.Add(object);
    return true;
}
