// Opens the DirectSound buffer record for a channel, 0040A180.
#include "shared/audio.hpp"
#include "shared/crt_memory.hpp"

int __fastcall Audio_DS_Channel_Open(AudioChannel *channel)
{
    AudioChannelBuffer *record = new AudioChannelBuffer;
    memset(record, 0, sizeof(*record));
    channel->DriverBuffer = record;
    record->Channel = channel;
    channel->unknown_1a8 = 264;
    channel->unknown_1b0 = 1056;
    record->Decode_Block = 0;
    record->Input = 0;
    record->Output = 0;
    int &reset_state = record->unknown_a8;
    reset_state = 0;
    Audio_Channel_Set_Format(record->Channel, &record->Channel->Device->DefaultFormat);
    return 0;
}
