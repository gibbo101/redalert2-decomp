// void __fastcall Audio_List_Init_Node(AudioListNode *node) -- 0x00407200
// Purpose: makes node an unlinked entry with priority 0.
#include "shared/audio.hpp"

void __fastcall Audio_List_Init_Node(AudioListNode *node)
{
    node->Next = node;
    node->Prev = node;
    node->Priority = 0;
}
