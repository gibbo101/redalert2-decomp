// void __fastcall Audio_List_Add_Descending(AudioListNode *list, AudioListNode *node) -- 0x00407260
// Purpose: links node in before the first entry whose priority is not
// higher than node's (at the tail when there is none;
// Audio_List_Next_Unchecked and Audio_List_Add_Tail expanded inline).
#include "shared/audio.hpp"

void __fastcall Audio_List_Add_Descending(AudioListNode *list, AudioListNode *node)
{
    int priority = node->Priority;
    AudioListNode *at = list;
    while ((at = Audio_List_Next_Unchecked(at)) != 0) {
        if (at->Priority <= priority) {
            Audio_List_Add_Tail(at, node);
            return;
        }
    }
    Audio_List_Add_Tail(list, node);
}
