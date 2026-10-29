#include "shared/wol_sink.hpp"
bool WolChannelDictionary::Remove_00767d60(Wstring const &key, WOL::Channel *old_value)
{
    if (Count == 0) return false;
    float load = (float)(Count - 1);
    load /= (float)BucketCount;
    unsigned int bucket = Key_Hash(key);
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
        if (load <= ShrinkLimit) Shrink_Table();
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
    if (load <= ShrinkLimit) Shrink_Table();
    return removed;
}
