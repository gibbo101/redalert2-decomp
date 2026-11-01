// void __fastcall Audio_Event_Jump_Pan(AudioEvent *event, int pan) -- 0x00406260
// Purpose: sets the event's pan (0..0x4000) at once instead of ramping to it.
#include "shared/audio_event.hpp"

void __fastcall Audio_Event_Jump_Pan(AudioEvent *event, int pan)
{
    if (pan > 0x4000u) {
        pan = 0x4000;
    } else if (pan < 0) {
        pan = 0;
    }
    event->Levels.Pan.Set(pan);
}
