// void __fastcall Audio_Channel_Destroy(AudioChannel *channel) -- 0x00402550
// Purpose: stops the channel as Audio_Channel_Stop does, detaches it
// from its device (0x004028B0), closes it in the driver and deletes it.
// @ref ?Audio_Channel_Detach@@YIXPAUAudioChannel@@@Z=004028b0
#include "shared/audio.hpp"

void __cdecl operator delete(void *block);

void __fastcall Audio_Channel_Destroy(AudioChannel *channel)
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
    Audio_Channel_Detach(channel);
    channel->Driver->Close(channel);
    operator delete(channel);
}
