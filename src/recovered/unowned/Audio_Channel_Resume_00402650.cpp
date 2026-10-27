// void __fastcall Audio_Channel_Resume(AudioChannel *channel) -- 0x00402650
// Purpose: under the driver lock, resumes a paused channel in the driver
// and marks it playing.
#include "shared/audio.hpp"

void __fastcall Audio_Channel_Resume(AudioChannel *channel)
{
    channel->Driver->Lock(channel);
    if (channel->Flags & AUDIO_CHANNEL_PAUSED) {
        channel->Driver->Resume(channel);
        channel->Flags &= ~AUDIO_CHANNEL_PAUSED;
        channel->Flags |= AUDIO_CHANNEL_PLAYING;
    }
    channel->Driver->Unlock(channel);
}
