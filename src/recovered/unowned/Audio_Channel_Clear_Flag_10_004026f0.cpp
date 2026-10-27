// void __fastcall Audio_Channel_Clear_Flag_10(AudioChannel *channel) -- 0x004026F0
// Purpose: clears channel flag 0x10 under the driver lock.
#include "shared/audio.hpp"

void __fastcall Audio_Channel_Clear_Flag_10(AudioChannel *channel)
{
    channel->Driver->Lock(channel);
    channel->Flags &= ~AUDIO_CHANNEL_FLAG_10;
    channel->Driver->Unlock(channel);
}
