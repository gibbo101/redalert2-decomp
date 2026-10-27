// void __fastcall Audio_Event_Set_Pan(AudioEvent *event, int pan) -- 0x00406280
// Purpose: sets the pan (0..0x4000) of an event: ramped while the event is
// fading (state 3), at once otherwise.
#include "shared/audio_event.hpp"

void __fastcall Audio_Event_Set_Pan(AudioEvent *event, int pan)
{
    if (event->State == 3) {
        int value = pan;
        if (value > 0x4000u) {
            value = 0x4000;
        } else if (value < 0) {
            value = 0;
        }
        event->Levels.Pan.Set_Target(value);
    } else {
        int value = pan;
        if (value > 0x4000u) {
            value = 0x4000;
        } else if (value < 0) {
            value = 0;
        }
        event->Levels.Pan.Set(value);
    }
}
