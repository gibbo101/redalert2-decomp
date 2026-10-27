// AudioListNode *__fastcall Audio_List_Next(AudioListNode *node) -- 0x00407310
// Purpose: the entry after node, or 0 at the end of the list or for a null node.
#include "shared/audio.hpp"

AudioListNode *__fastcall Audio_List_Next(AudioListNode *node)
{
    if (node == 0) {
        return 0;
    }
    AudioListNode *next = node->Next;
    if (next != 0 && (int)next == next->Priority) {
        return 0;
    }
    return next;
}
