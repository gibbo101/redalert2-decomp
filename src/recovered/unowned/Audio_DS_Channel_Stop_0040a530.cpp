// int __fastcall Audio_DS_Channel_Stop(AudioChannel *channel) -- 0x0040A530
// Purpose: for a playing or paused channel, stops its buffer and runs the
// channel's stop callback (+0x164). Returns 0.
#include "shared/audio.hpp"

int __fastcall Audio_DS_Channel_Stop(AudioChannel *channel)
{
    if (channel->Flags & (AUDIO_CHANNEL_PLAYING | AUDIO_CHANNEL_PAUSED)) {
        if (channel->DriverBuffer->Buffer != 0) {
            channel->DriverBuffer->Buffer->Stop();
        }
        if (channel->unknown_stop_callback_164 != 0) {
            channel->unknown_stop_callback_164(channel);
        }
    }
    return 0;
}
