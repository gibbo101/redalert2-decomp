// AudioListNode *__fastcall Audio_List_First(AudioListNode *list) -- 0x004072F0
// Purpose: the first entry of the list, or 0 when it is empty or null.
#include "shared/audio.hpp"

AudioListNode *__fastcall Audio_List_First(AudioListNode *list)
{
    if (list == 0) {
        return 0;
    }
    AudioListNode *first = list->Next;
    if (first != 0 && (int)first == first->Priority) {
        return 0;
    }
    return first;
}
