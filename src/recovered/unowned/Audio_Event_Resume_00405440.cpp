// void __fastcall Audio_Event_Resume(AudioEvent *event) -- 0x00405440
// Purpose: lifts one pause from the event; a playing one (state 2) whose
// pauses are all gone has its start time moved forward by the current time.
// @ref ?Audio_Now@@YI_JXZ=004092d0
#include "shared/audio_event.hpp"

void __fastcall Audio_Event_Resume(AudioEvent *event)
{
    if (event->PauseCount != 0) {
        if (--event->PauseCount < 0) {
            event->PauseCount = 0;
        }
        if (event->PauseCount == 0 && event->State == 2) {
            event->unknown_140 += Audio_Now();
        }
    }
}
