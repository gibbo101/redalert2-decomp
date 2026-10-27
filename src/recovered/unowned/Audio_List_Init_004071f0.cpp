// void __fastcall Audio_List_Init(AudioListNode *list) -- 0x004071F0
// Purpose: makes list an empty list head (links and priority point to
// itself).
#include "shared/audio.hpp"

void __fastcall Audio_List_Init(AudioListNode *list)
{
    list->Next = list;
    list->Prev = list;
    list->Priority = (int)list;
}
