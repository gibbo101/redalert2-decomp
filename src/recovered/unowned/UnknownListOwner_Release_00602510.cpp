// int UnknownListOwner_00602510::Release_00602510(unsigned char flags) (0x00602510)
// As Release_00600350, then deletes the object itself when bit 0 of flags is set; returns it.
#include "shared/unknown_list_owners.hpp"
#include "shared/wide_string.hpp"

int UnknownListOwner_00602510::Release_00602510(unsigned char flags)
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
    if (flags & 1) {
        delete this;
    }
    return (int)this;
}
