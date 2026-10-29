#include "shared/wol_sink.hpp"
void WolChannelDictionary::Clear_00766400()
{
    for (unsigned int index = 0; index < BucketCount; ++index) {
        Node *node = Buckets[index];
        while (node) {
            Node *old = node;
            node = node->Next;
            delete old;
        }
        Buckets[index] = 0;
    }
    Count = 0;
    while (Get_Size() > MinimumBuckets && !ResizeLocked) Shrink_Table();
}
