// void __fastcall Audio_Event_Set_Volume(AudioEvent *event, int volume) -- 0x004061E0
// Purpose: sets the volume (0..0x4000) of an event, scaled by the event
// type's own volume: ramped while fading (state 3), at once otherwise.
#include "shared/audio_event.hpp"

void __fastcall Audio_Event_Set_Volume(AudioEvent *event, int volume)
{
    if (event->State == 3) {
        int value = volume;
        if (value > 0x4000u) {
            value = 0x4000;
        } else if (value < 0) {
            value = 0;
        }
        event->Levels.Volume.Set_Target((event->Type->VolumeLevel.Current >> 16) * value >> 14);
    } else {
        int value = volume;
        if (value > 0x4000u) {
            value = 0x4000;
        } else if (value < 0) {
            value = 0;
        }
        event->Levels.Volume.Set((event->Type->VolumeLevel.Current >> 16) * value >> 14);
        event->Levels.Volume.Update();
    }
}
