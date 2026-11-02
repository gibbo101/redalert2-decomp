// void WolDictionary<unsigned int, OwnerDraw::UnknownControlRecord>::Shrink_Table() (0x006027E0): the
// control registry 0x00A73640 (nodes of 0x208 bytes; called from 0x00601C50).
// The out-of-line shrink() (wlib Dictionary::shrink, shared/wol_dictionary.hpp's Shrink_Table) of one of
// ownrdraw.cpp's dictionaries. Written as an explicit specialization with the template's body: its callers
// (unrecovered window procedures) are what emit the implicit instance in the original; when they land, drop
// this specialization (it must precede their uses) and let the template instantiate.
#include "shared/wol_dictionary.hpp"
#include "shared/owner_draw_dialog_control.hpp"

template<> void WolDictionary<unsigned int, OwnerDraw::UnknownControlRecord>::Shrink_Table()
{
    if (BucketCount > MinimumBuckets && ResizeLocked != true) {
        int old_count = BucketCount;
        Node **old_buckets = Buckets;
        BucketCount >>= 1;
        --Bits;
        Buckets = new Node *[BucketCount];
        memset(Buckets, 0, BucketCount * sizeof(Node *));
        for (int index = 0; index < old_count; ++index) {
            Node *node = old_buckets[index];
            while (node) {
                unsigned int hash = Hash(node->Key);
                unsigned int bucket = ((1u << Bits) - 1) & hash;
                Node *head = Buckets[bucket];
                Buckets[bucket] = node;
                Node *next = node->Next;
                node->Next = head;
                node = next;
            }
        }
        delete [] old_buckets;
    }
}
