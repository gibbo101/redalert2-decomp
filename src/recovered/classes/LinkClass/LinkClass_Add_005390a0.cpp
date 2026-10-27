// LinkClass &LinkClass::Add(LinkClass &list) (0x005390A0)
// Inserts the node after list; returns the head of the list.
#include "shared/gadget.hpp"

LinkClass &LinkClass::Add(LinkClass &list)
{
    LinkClass *next = list.Next;
    list.Next = this;
    Prev = &list;
    Next = next;
    if (next != 0) {
        next->Prev = this;
    }
    return Head_Of_List();
}
