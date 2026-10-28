// void UnknownNodeList_006003D0::unknown_remove_node(UnknownNode_006003d0 *node) -- 0x00600410
// Unlinks the node from the list at +0x34 and frees it (nothing when it is
// not in the list).
#include "shared/unknown_node_list.hpp"
// @ref ??3@YAXPAX@Z=00781d3b

void UnknownNodeList_006003d0::unknown_remove_node(UnknownNode_006003d0 *node)
{
    UnknownNode_006003d0 *previous = 0;
    UnknownNode_006003d0 *current = Head;
    while (current != 0) {
        if (node == current) {
            break;
        }
        previous = current;
        current = current->Next;
    }
    if (current != 0) {
        if (previous != 0) {
            previous->Next = current->Next;
        } else {
            Head = current->Next;
        }
        operator delete(current);
    }
}
