#ifndef RA2_SHARED_WOL_LADDER_CACHE_RESIZE_HPP
#define RA2_SHARED_WOL_LADDER_CACHE_RESIZE_HPP
#include "shared/wol_sink.hpp"
// Shrinks and rehashes one WOnline ladder cache. Remove and the standalone
// Shrink method share the same observed operation. Writes the new bucket
// head before reading/relinking the old node's next pointer, as in the target.
static inline void Shrink_Cache_Table(WolLadderCache &cache)
{
    typedef WolLadderCache::Node Node;

    if (cache.BucketCount > cache.MinimumBuckets && cache.ResizeLocked != true) {
        int old_count = cache.BucketCount;
        Node **old_buckets = cache.Buckets;
        cache.BucketCount >>= 1;
        --cache.Bits;
        cache.Buckets = new Node *[cache.BucketCount];
        memset(cache.Buckets, 0, cache.BucketCount * sizeof(Node *));
        if (old_count > 0) {
            Node **bucket = old_buckets;
            int remaining = old_count;
            do {
                Node *node = *bucket;
                while (node) {
                    unsigned int hash = cache.Hash(node->Key);
                    unsigned int index = ((1u << cache.Bits) - 1) & hash;
                    Node *head = cache.Buckets[index];
                    cache.Buckets[index] = node;
                    Node *next = node->Next;
                    node->Next = head;
                    node = next;
                }
                ++bucket;
            } while (--remaining);
        }
        delete [] old_buckets;
    }
}
#endif
