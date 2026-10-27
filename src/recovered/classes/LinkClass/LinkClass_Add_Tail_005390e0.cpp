// LinkClass &LinkClass::Add_Tail(LinkClass &list) (0x005390E0)
// Appends the node after list's tail; returns the head of the list.
#include "shared/gadget.hpp"

LinkClass &LinkClass::Add_Tail(LinkClass &list)
{
    LinkClass *tail = &list.Tail_Of_List();
    tail->Next = this;
    Prev = tail;
    Next = 0;
    return Head_Of_List();
}
