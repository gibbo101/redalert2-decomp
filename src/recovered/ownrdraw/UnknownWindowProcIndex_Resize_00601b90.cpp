#include "shared/crt_memory.hpp"
#include "shared/owner_draw_dialog_control.hpp"

namespace OwnerDraw {

// Doubles the bucket count and moves every node to its new bucket; a fixed-size table is left alone
// (0x00601B90).
void UnknownWindowProcIndex::Resize()
{
    if (Fixed_Size == true) {
        return;
    }
    int old_size = Size;
    Node **old_buckets = Buckets;
    Size = old_size * 2;
    Bits++;
    Buckets = (Node **)operator new(Size * sizeof(Node *));
    memset(Buckets, 0, Size * sizeof(Node *));
    for (int index = 0; index < old_size; index++) {
        Node *node = old_buckets[index];
        while (node != 0) {
            unsigned int offset = Bucket_Index(node->Key);
            Node *head = Buckets[offset];
            Buckets[offset] = node;
            Node *next = node->Next;
            node->Next = head;
            node = next;
        }
    }
    operator delete(old_buckets);
}

}
