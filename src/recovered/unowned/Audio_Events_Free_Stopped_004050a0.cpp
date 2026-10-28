// void Audio_Events_Free_Stopped() -- 0x004050A0
// Purpose: frees every event that has been stopped.
#include "shared/audio_event.hpp"

void Audio_Events_Free_Stopped()
{
    if (Audio_Events_Ready != 0) {
        AudioEvent *event = (AudioEvent *)Audio_Event_List.Next;
        while (event != (AudioEvent *)&Audio_Event_List) {
            AudioEvent *next = (AudioEvent *)event->Next;
            if (event->Flags & AUDIO_EVENT_STOPPED) {
                AUDIO_EVENT_FREE_INLINE(event)
            }
            event = next;
        }
    }
}
