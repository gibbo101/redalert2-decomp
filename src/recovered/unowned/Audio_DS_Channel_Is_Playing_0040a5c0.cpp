// int __fastcall Audio_DS_Channel_Is_Playing(AudioChannel *channel) -- 0x0040A5C0
// Purpose: the playing bit of the buffer status, or 0 without a buffer or
// when GetStatus fails.
#include "shared/audio.hpp"

int __fastcall Audio_DS_Channel_Is_Playing(AudioChannel *channel)
{
    AudioChannelBuffer *record = channel->DriverBuffer;
    DWORD status;
    if (record->Buffer != 0 && record->Buffer->GetStatus(&status) == DS_OK) {
        return status & DSBSTATUS_PLAYING;
    }
    return 0;
}
