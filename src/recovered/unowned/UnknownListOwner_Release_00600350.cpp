// void UnknownListOwner_00600350::Release_00600350() (0x00600350)
// Frees the block, removes and frees every list node and deletes the string.
#include "shared/unknown_list_owners.hpp"
#include "shared/wide_string.hpp"

void UnknownListOwner_00600350::Release_00600350()
{
    if (Block) {
        delete Block;
        Block = 0;
    }
    while (List) {
        UnknownListNode *node = List;
        UnknownListNode *previous = 0;
        for (UnknownListNode *cursor = List; cursor; cursor = cursor->Next) {
            if (node == cursor) {
                if (cursor != 0) {
                    if (previous != 0) {
                        previous->Next = cursor->Next;
                    } else {
                        List = cursor->Next;
                    }
                    delete cursor;
                }
                break;
            }
            previous = cursor;
        }
    }
    if (Text) {
        delete Text;
    }
}
