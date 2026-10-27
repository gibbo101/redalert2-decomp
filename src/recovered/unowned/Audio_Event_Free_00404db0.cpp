// void __fastcall Audio_Event_Free(AudioEvent *event) -- 0x00404DB0
// Purpose: unlinks the event and frees it: deleted when it was allocated,
// else returned to the event pool. One event less.
// @ref ?Audio_Event_Count@@3HA=00830fa4
// @ref ?Audio_Event_Pool@@3PAUAudioPool@@A=00830fc0
#include "shared/audio_event.hpp"

void __cdecl operator delete(void *block);

void __fastcall Audio_Event_Free(AudioEvent *event)
{
    Audio_List_Remove(event);
    event->unknown_138 = 0;
    if (event->Flags & AUDIO_EVENT_ALLOCATED) {
        operator delete(event);
    } else {
        Audio_Pool_Free(Audio_Event_Pool, event);
    }
    Audio_Event_Count--;
}
