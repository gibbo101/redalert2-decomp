// LinkClass &LinkClass::Add_Head(LinkClass &list) (0x005390C0)
// Puts the node in front of list's head.
#include "shared/gadget.hpp"

LinkClass &LinkClass::Add_Head(LinkClass &list)
{
    LinkClass *head = &list.Head_Of_List();
    head->Prev = this;
    Next = head;
    Prev = 0;
    return *this;
}
