// void Audio_Events_Clear() -- 0x00404E50
// Purpose: stops and frees every event.
#include "shared/audio_event.hpp"

void Audio_Events_Clear()
{
    if (Audio_Events_Ready != 0) {
        AudioEvent *event = (AudioEvent *)Audio_Event_List.Next;
        while (event != (AudioEvent *)&Audio_Event_List) {
            AudioEvent *next = (AudioEvent *)event->Next;
            if (!(event->Flags & AUDIO_EVENT_STOPPED)) {
                AUDIO_EVENT_DETACH_INLINE(event)
                AUDIO_EVENT_RELEASE_SAMPLES_INLINE(event)
                AUDIO_EVENT_MARK_STOPPED(event)
            }
            AUDIO_EVENT_FREE_INLINE(event)
            event = next;
        }
    }
}
