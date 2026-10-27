// HashObject<K, V>: the key/value element of Westwood's hash tables (the map's subzone
// tables, the color scheme table, the radar tracking table). Moved from shared/map.hpp.
#ifndef RA2_SHARED_HASH_OBJECT_HPP
#define RA2_SHARED_HASH_OBJECT_HPP

// Key/value element of the map's hash tables (empty constructor).
template <class K, class V>
struct HashObject {
    HashObject() {}
    // Member-wise (VectorClass<HashObject<unsigned int, unsigned int> >::Fetch 0x0056AD90).
    HashObject(HashObject const &other) : Key(other.Key), Value(other.Value) {}
    K Key;
    V Value;
};

// The bucket vectors compare keys only (VectorClass<HashObject<...>>::operator== 0x0056BEF0
// and the ID lookups).
template <class K, class V>
inline bool operator==(HashObject<K, V> const &a, HashObject<K, V> const &b) { return a.Key == b.Key; }
template <class K, class V>
inline bool operator!=(HashObject<K, V> const &a, HashObject<K, V> const &b) { return a.Key != b.Key; }

#endif
