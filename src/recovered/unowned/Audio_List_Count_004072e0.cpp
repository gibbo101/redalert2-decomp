// int __fastcall Audio_List_Count(AudioListNode *list) -- 0x004072E0
// Purpose: the number of entries in the list.
#include "shared/audio.hpp"

int __fastcall Audio_List_Count(AudioListNode *list)
{
    int count = 0;
    for (AudioListNode *node = list->Next; node != list; node = node->Next) {
        count++;
    }
    return count;
}
