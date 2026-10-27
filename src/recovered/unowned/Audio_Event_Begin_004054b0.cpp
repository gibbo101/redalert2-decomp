// int __fastcall Audio_Event_Begin(AudioEvent *event) -- 0x004054B0
// Purpose: starts the channel of an event that was waiting (flag 8): puts its
// source on the channel, sets the starting frequency and volume and starts
// it. Returns 1 when the channel runs; otherwise the event goes back to
// state 1 (waiting for its source).
#include "shared/audio_event.hpp"

int __fastcall Audio_Event_Begin(AudioEvent *event)
{
    if (event != event->Channel->Owner) {
        return 0;
    }
    Audio_Channel_Lock(event->Channel);
    int source = event->unknown_148;
    event->Flags |= 8;
    Audio_Channel_Set_Source(event->Channel, (AudioSource *)source);
    event->Channel->Levels.Frequency.Set(event->unknown_14c);
    int volume = 0x4000;
    if (event->unknown_150 > 0) {
        volume = 0x4000 - (unsigned int)(event->unknown_150 << 14) / 100;
    }
    event->Channel->Levels.Volume.Set(volume);
    event->State = 3;
    event->Flags |= 2;
    event->unknown_148 = 0;
    if (Audio_Channel_Start(event->Channel) != 0) {
        event->State = 1;
        event->unknown_148 = source;
        event->Flags &= ~2;
        Audio_Channel_Unlock(event->Channel);
        return 0;
    }
    Audio_Channel_Unlock(event->Channel);
    return 1;
}
