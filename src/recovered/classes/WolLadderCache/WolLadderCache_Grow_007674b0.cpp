#include "shared/wol_sink.hpp"
void WolLadderCache::Grow_007674b0()
{
    if (ResizeLocked != true) {
        int old_count = BucketCount;
        Node **old_buckets = Buckets;
        BucketCount *= 2;
        ++Bits;
        Buckets = new Node *[BucketCount];
        memset(Buckets, 0, BucketCount * sizeof(Node *));
        if (old_count > 0) {
            Node **bucket = old_buckets;
            int remaining = old_count;
            do {
                Node *node = *bucket;
                while (node) {
                    unsigned int hash = Hash(node->Key);
                    unsigned int index = ((1u << Bits) - 1) & hash;
                    Node *head = Buckets[index];
                    Buckets[index] = node;
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
