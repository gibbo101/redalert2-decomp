#include "shared/owner_draw_dialog_control.hpp"

namespace OwnerDraw {

// Looks up key; on a hit stores its window procedure slot in value and returns true (0x006018E0).
bool UnknownWindowProcIndex::Get(HWND const &key, WNDPROC *&value) const
{
    int offset;
    Node *node;
    if (Count == 0) {
        return false;
    }
    offset = Bucket_Index(key);
    node = Buckets[offset];
    if (node == 0) {
        return false;
    }
    while ((node != 0) && !(node->Key == key)) {
        node = node->Next;
    }
    if (node == 0) {
        return false;
    }
    value = &node->Value;
    return true;
}

}
