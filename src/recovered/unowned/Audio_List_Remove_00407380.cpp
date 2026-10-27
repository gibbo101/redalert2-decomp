// void __fastcall Audio_List_Remove(AudioListNode *node) -- 0x00407380
// Purpose: unlinks node from its list and leaves it linked to itself.
#include "shared/audio.hpp"

void __fastcall Audio_List_Remove(AudioListNode *node)
{
    node->Prev->Next = node->Next;
    node->Next->Prev = node->Prev;
    node->Next = node;
    node->Prev = node;
}
