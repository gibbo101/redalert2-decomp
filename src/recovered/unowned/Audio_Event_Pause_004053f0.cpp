// void __fastcall Audio_Event_Pause(AudioEvent *event) -- 0x004053F0
// Purpose: one more pause on the event; a playing one (state 2) with its
// first pause has its start time moved back by the current time.
// @ref ?Audio_Now@@YA_JXZ=004092d0
#include "shared/audio_event.hpp"

void __fastcall Audio_Event_Pause(AudioEvent *event)
{
    if (event->PauseCount == 0 && event->State == 2) {
        event->unknown_140 -= Audio_Now();
    }
    event->PauseCount++;
}
