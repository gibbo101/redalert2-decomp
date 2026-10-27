// void __fastcall Audio_List_Add_Tail(AudioListNode *list, AudioListNode *node) -- 0x00407350
// Purpose: links node in before list (at the tail of the circular list).
#include "shared/audio.hpp"

void __fastcall Audio_List_Add_Tail(AudioListNode *list, AudioListNode *node)
{
    node->Prev = list->Prev;
    node->Next = list;
    list->Prev = node;
    node->Prev->Next = node;
}
