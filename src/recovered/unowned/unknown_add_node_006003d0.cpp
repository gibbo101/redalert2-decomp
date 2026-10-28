// void UnknownNodeList_006003D0::unknown_add_node(int length) -- 0x006003D0
// Purpose: allocates a node with room for `length` 16-bit characters plus
// a 16-byte header (data pointer at +0x08 to its own +0x10, +0x04 = 0)
// and pushes it on the list at +0x34.
// Owner and node layouts: shared/unknown_node_list.hpp.
#include "shared/unknown_node_list.hpp"
// @ref ??2@YAPAXI@Z=00782017

void UnknownNodeList_006003d0::unknown_add_node(int length)
{
    UnknownNode_006003d0 *node = (UnknownNode_006003d0 *)operator new(length * 2 + 0x12);
    if (node != 0) {
        node->Data = node->Text;
        node->Next = Head;
        node->unknown_04 = 0;
        Head = node;
    }
}
