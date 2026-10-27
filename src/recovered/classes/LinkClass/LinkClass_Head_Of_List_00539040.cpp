// LinkClass &LinkClass::Head_Of_List() (0x00539040)
// The first node (following Prev; stops if the list loops back).
#include "shared/gadget.hpp"

LinkClass &LinkClass::Head_Of_List()
{
    LinkClass *link = this;
    while (link->Prev != 0) {
        link = link->Prev;
        if (link == this) {
            break;
        }
    }
    return *link;
}
