// AudioListNode *__fastcall Audio_List_Nth(AudioListNode *list, int index) -- 0x00407330
// Purpose: the entry at position index of the list, or 0 when the list is
// shorter.
#include "shared/audio.hpp"

AudioListNode *__fastcall Audio_List_Nth(AudioListNode *list, int index)
{
    for (AudioListNode *node = list->Next; node != list; node = node->Next) {
        if (index-- == 0) {
            return node;
        }
    }
    return 0;
}
