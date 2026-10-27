// int __fastcall Audio_List_Add_Ascending(AudioListNode *list, AudioListNode *node) -- 0x00407210
// Purpose: links node in before the first entry whose priority is not
// lower than node's (at the tail when there is none) and returns the
// number of entries before it (Audio_List_Next_Unchecked and
// Audio_List_Add_Tail expanded inline).
#include "shared/audio.hpp"

int __fastcall Audio_List_Add_Ascending(AudioListNode *list, AudioListNode *node)
{
    int priority = node->Priority;
    int position = 0;
    AudioListNode *at = list;
    while ((at = Audio_List_Next_Unchecked(at)) != 0) {
        if (priority <= at->Priority) {
            Audio_List_Add_Tail(at, node);
            return position;
        }
        position++;
    }
    Audio_List_Add_Tail(list, node);
    return position;
}
