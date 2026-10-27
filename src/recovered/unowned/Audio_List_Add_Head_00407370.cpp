// void __fastcall Audio_List_Add_Head(AudioListNode *list, AudioListNode *node) -- 0x00407370
// Purpose: links node in after list (at the head of the circular list).
#include "shared/audio.hpp"

void __fastcall Audio_List_Add_Head(AudioListNode *list, AudioListNode *node)
{
    node->Prev = list;
    node->Next = list->Next;
    list->Next = node;
    node->Next->Prev = node;
}
