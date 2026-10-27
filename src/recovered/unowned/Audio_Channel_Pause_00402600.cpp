// void __fastcall Audio_Channel_Pause(AudioChannel *channel) -- 0x00402600
// Purpose: under the driver lock, pauses a playing channel in the driver
// and marks it paused.
#include "shared/audio.hpp"

void __fastcall Audio_Channel_Pause(AudioChannel *channel)
{
    channel->Driver->Lock(channel);
    if (channel->Flags & AUDIO_CHANNEL_PLAYING) {
        channel->Flags &= ~AUDIO_CHANNEL_PLAYING;
        channel->Driver->Pause(channel);
        channel->Flags |= AUDIO_CHANNEL_PAUSED;
    }
    channel->Driver->Unlock(channel);
}
