// void __fastcall Audio_Channel_Stop(AudioChannel *channel) -- 0x004025B0
// Purpose: under the driver lock, stops a playing or paused channel in the
// driver; then runs the channel's end callback (+0xBC) and detaches its
// source.
#include "shared/audio.hpp"

void __fastcall Audio_Channel_Stop(AudioChannel *channel)
{
    channel->Driver->Lock(channel);
    if (channel->Flags & (AUDIO_CHANNEL_PLAYING | AUDIO_CHANNEL_PAUSED)) {
        channel->Driver->Stop(channel);
    }
    channel->Driver->Unlock(channel);
    if (channel->unknown_end_callback_bc != 0) {
        channel->unknown_end_callback_bc(channel);
    }
    channel->Source = 0;
}
