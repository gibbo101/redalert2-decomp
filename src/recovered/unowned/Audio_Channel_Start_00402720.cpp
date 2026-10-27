// HRESULT __fastcall Audio_Channel_Start(AudioChannel *channel) -- 0x00402720
// Purpose: starts a channel that is neither playing nor paused and has a
// source: updates its levels and combined settings, and under the driver lock starts
// it in the driver, marking it playing on success. Returns the driver's
// result, 0x800F0000 when the channel is already active or 0x80070000
// without a source.
// @ref ?Update@AudioLevelSet@@QAEXXZ=00401080
// @ref ?Audio_Channel_Update_Settings@@YIXPAUAudioChannel@@@Z=00402220
#include "shared/audio.hpp"

HRESULT __fastcall Audio_Channel_Start(AudioChannel *channel)
{
    if (channel->Flags & (AUDIO_CHANNEL_PLAYING | AUDIO_CHANNEL_PAUSED)) {
        return 0x800f0000;
    }
    if (channel->Source == 0) {
        return 0x80070000;
    }
    channel->Levels.Update();
    Audio_Channel_Update_Settings(channel);
    channel->Driver->Lock(channel);
    HRESULT result = channel->Driver->Start(channel);
    if (result == DS_OK) {
        channel->Flags |= AUDIO_CHANNEL_PLAYING;
    }
    channel->Driver->Unlock(channel);
    return result;
}
