// void __fastcall Audio_Event_Release_Samples(AudioEvent *event) -- 0x00404D60
// Purpose: lets go of the event's samples (0x00401F90 on each bank entry)
// and forgets them.
#include "shared/audio_event.hpp"

void __fastcall Audio_Event_Release_Samples(AudioEvent *event)
{
    for (int i = 0; i < event->SampleCount; i++) {
        ((AudioCountedList *)event->Samples[i])->Leave();
        event->Samples[i] = 0;
    }
    event->SampleCount = 0;
}
