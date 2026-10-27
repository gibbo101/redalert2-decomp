// int __fastcall Audio_DS_Channel_Pause(AudioChannel *channel) -- 0x0040A570
// Purpose: stops the channel's buffer, if it has one. Returns 0.
#include "shared/audio.hpp"

int __fastcall Audio_DS_Channel_Pause(AudioChannel *channel)
{
    AudioChannelBuffer *record = channel->DriverBuffer;
    if (record->Buffer != 0) {
        record->Buffer->Stop();
    }
    return 0;
}
