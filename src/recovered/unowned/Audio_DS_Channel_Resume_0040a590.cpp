// HRESULT __fastcall Audio_DS_Channel_Resume(AudioChannel *channel) -- 0x0040A590
// Purpose: plays the channel's buffer looping again. Returns 0, or
// 0x80040000 without a buffer or when Play fails.
#include "shared/audio.hpp"

HRESULT __fastcall Audio_DS_Channel_Resume(AudioChannel *channel)
{
    AudioChannelBuffer *record = channel->DriverBuffer;
    if (record->Buffer != 0 && record->Buffer->Play(0, 0, DSBPLAY_LOOPING) == DS_OK) {
        return DS_OK;
    }
    return 0x80040000;
}
