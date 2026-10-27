// void __fastcall Audio_Channel_Release(AudioChannel *channel, int value) -- 0x00402440
// Purpose: stores value at +0x0C, stops the channel as Audio_Channel_Stop
// does and marks it free (flag 8).
#include "shared/audio.hpp"

void __fastcall Audio_Channel_Release(AudioChannel *channel, int value)
{
    channel->unknown_0c = value;
    channel->Driver->Lock(channel);
    if (channel->Flags & (AUDIO_CHANNEL_PLAYING | AUDIO_CHANNEL_PAUSED)) {
        channel->Driver->Stop(channel);
    }
    channel->Driver->Unlock(channel);
    if (channel->unknown_end_callback_bc != 0) {
        channel->unknown_end_callback_bc(channel);
    }
    channel->Source = 0;
    channel->Flags |= AUDIO_CHANNEL_FREE;
}
