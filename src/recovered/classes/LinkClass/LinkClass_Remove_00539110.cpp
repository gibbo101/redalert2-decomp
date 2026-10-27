// LinkClass *LinkClass::Remove() (0x00539110)
// Unlinks the node; returns the head of what remains (null when it was alone).
#include "shared/gadget.hpp"

LinkClass *LinkClass::Remove()
{
    LinkClass *head = &Head_Of_List();
    LinkClass *tail = &Tail_Of_List();

    if (Prev != 0) {
        Prev->Next = Next;
    }
    if (Next != 0) {
        Next->Prev = Prev;
    }
    Prev = 0;
    Next = 0;

    if (head == this) {
        if (tail == this) {
            return 0;
        }
        return &tail->Head_Of_List();
    }
    return head;
}
