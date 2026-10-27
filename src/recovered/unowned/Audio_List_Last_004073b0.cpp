// AudioListNode *__fastcall Audio_List_Last(AudioListNode *list) -- 0x004073B0
// Purpose: the last entry of the list, or 0 when it is empty.
#include "shared/audio.hpp"

AudioListNode *__fastcall Audio_List_Last(AudioListNode *list)
{
    AudioListNode *last = list->Prev;
    return (int)last == last->Priority ? 0 : last;
}
