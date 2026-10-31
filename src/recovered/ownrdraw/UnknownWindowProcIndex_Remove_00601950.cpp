#include "shared/crt_memory.hpp"
#include "shared/owner_draw_dialog_control.hpp"

namespace OwnerDraw {

// Halves the bucket count and moves every node to its new bucket (inline in 0x00601950).
inline void UnknownWindowProcIndex::Shrink()
{
    unsigned int old_size = Size;
    Node **old_buckets = Buckets;
    Size = old_size >> 1;
    Bits--;
    Buckets = (Node **)operator new(Size * sizeof(Node *));
    memset(Buckets, 0, Size * sizeof(Node *));
    for (int index = 0; index < (int)old_size; index++) {
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

// Removes key, passing its window procedure back in value; the table shrinks once its load falls to
// Min_Load (0x00601950).
bool UnknownWindowProcIndex::Remove(HWND const &key, WNDPROC &value)
{
    if (Count == 0) {
        return false;
    }
    float load = (float)(Count - 1);
    load /= Size;
    int offset = Bucket_Index(key);
    Node *node = Buckets[offset];
    if (node == 0) {
        return false;
    }
    if (node->Key == key) {
        value = node->Value;
        Node *next = Buckets[offset]->Next;
        operator delete(Buckets[offset]);
        Buckets[offset] = next;
        Count--;
        if (load <= Min_Load && Size > Min_Size && Fixed_Size != true) {
            Shrink();
        }
        return true;
    }
    bool removed = false;
    Node *next = node->Next;
    while (next != 0) {
        if (next->Key == key) {
            value = next->Value;
            node->Next = next->Next;
            Count--;
            operator delete(next);
            removed = true;
            break;
        }
        node = next;
        next = next->Next;
    }
    if (load <= Min_Load && Size > Min_Size && Fixed_Size != true) {
        Shrink();
    }
    return removed;
}

}
