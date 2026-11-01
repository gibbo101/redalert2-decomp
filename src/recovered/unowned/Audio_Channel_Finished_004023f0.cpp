// int __fastcall Audio_Channel_Finished(AudioChannel *channel) -- 0x004023F0
// Purpose: the channel's default stop handler (+0x164): drops the source,
// clears the playing and paused flags and the loop count, resets the
// channel's levels and returns the done callback's (+0xB8) result, or 0.
// @ref ?Init@AudioLevelSet@@QAIXXZ=00401000
#include "shared/audio.hpp"

int __fastcall Audio_Channel_Finished(AudioChannel *channel)
{
    channel->Source = 0;
    channel->Flags &= ~(AUDIO_CHANNEL_PLAYING | AUDIO_CHANNEL_PAUSED);
    channel->LoopCount = 0;
    channel->Levels.Init();
    if (channel->unknown_done_b8 != 0) {
        return channel->unknown_done_b8(channel);
    }
    return 0;
}
