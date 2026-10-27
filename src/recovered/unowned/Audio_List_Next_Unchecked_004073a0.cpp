// AudioListNode *__fastcall Audio_List_Next_Unchecked(AudioListNode *node) -- 0x004073A0
// Purpose: the entry after node, or 0 at the end of the list (node must
// not be null).
#include "shared/audio.hpp"

AudioListNode *__fastcall Audio_List_Next_Unchecked(AudioListNode *node)
{
    AudioListNode *next = node->Next;
    if (next != 0 && (int)next == next->Priority) {
        return 0;
    }
    return next;
}
