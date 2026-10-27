// void __fastcall Audio_List_Move_All(AudioListNode *list, AudioListNode *destination) -- 0x004072B0
// Purpose: moves every entry of list to the tail of destination and leaves
// list empty.
#include "shared/audio.hpp"

void __fastcall Audio_List_Move_All(AudioListNode *list, AudioListNode *destination)
{
    AudioListNode *first = list->Next;
    AudioListNode *last = list->Prev;
    if (first != list) {
        AudioListNode *tail = destination->Prev;
        tail->Next = first;
        first->Prev = tail;
        last->Next = destination;
        destination->Prev = last;
        list->Next = list;
        list->Prev = list;
        list->Priority = (int)list;
    }
}
