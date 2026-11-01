// void __fastcall Audio_Event_Jump_Volume(AudioEvent *event, int volume) -- 0x004061A0
// Purpose: sets the event's volume (0..0x4000, scaled by its type's volume) at
// once instead of ramping to it.
#include "shared/audio_event.hpp"

void __fastcall Audio_Event_Jump_Volume(AudioEvent *event, int volume)
{
    int value = volume;
    if (value > 0x4000u) {
        value = 0x4000;
    } else if (value < 0) {
        value = 0;
    }
    event->Levels.Volume.Set((event->Type->VolumeLevel.Current >> 16) * value >> 14);
    event->Levels.Volume.Update();
}
