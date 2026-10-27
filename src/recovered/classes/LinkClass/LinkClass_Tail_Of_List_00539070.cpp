// LinkClass &LinkClass::Tail_Of_List() (0x00539070)
// The last node (following Next; stops if the list loops back).
#include "shared/gadget.hpp"

LinkClass &LinkClass::Tail_Of_List()
{
    LinkClass *link = this;
    while (link->Next != 0) {
        link = link->Next;
        if (link == this) {
            break;
        }
    }
    return *link;
}
