// void __fastcall Audio_Event_Stop(AudioEvent *event) -- 0x00405300
// Purpose: stops an event that is not stopped yet: takes it off its channel,
// lets go of its samples, and marks it stopped (state 4, flag 1).
#include "shared/audio_event.hpp"

void __fastcall Audio_Event_Stop(AudioEvent *event)
{
    if (!(event->Flags & AUDIO_EVENT_STOPPED)) {
        Audio_Event_Detach(event);
        Audio_Event_Release_Samples(event);
        AUDIO_EVENT_MARK_STOPPED(event)
    }
}
