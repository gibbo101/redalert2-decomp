#include "shared/wol_ladder_cache_resize.hpp"
bool WolLadderCache::Remove_00767160(Wstring const &key, WOL::Ladder *old_value)
{
    if (Count == 0) return false;
    float load = (float)(Count - 1);
    load /= (float)BucketCount;
    unsigned int hash = Hash(key);
    unsigned int bucket = ((1u << Bits) - 1) & hash;
    Node *head = Buckets[bucket];
    Node *previous = head;
    if (!head) return false;
    if (head->Key == key) {
        *old_value = head->Value;
        Node *removed = Buckets[bucket];
        Node *next = removed->Next;
        delete removed;
        Buckets[bucket] = next;
        --Count;
        if (load <= ShrinkLimit) Shrink_Cache_Table(*this);
        return true;
    }
    Node *node = head->Next;
    bool removed = false;
    while (node) {
        if (node->Key == key) {
            *old_value = node->Value;
            previous->Next = node->Next;
            --Count;
            delete node;
            removed = true;
            break;
        }
        previous = node;
        node = node->Next;
    }
    if (load <= ShrinkLimit) Shrink_Cache_Table(*this);
    return removed;
}
