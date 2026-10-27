// int __fastcall Audio_DS_Channel_Close(AudioChannel *channel) -- 0x0040A1F0
// Purpose: releases the channel's DirectSound buffer record: frees its two
// heap blocks (clearing their sizes), releases the buffer and deletes the
// record. Returns 0.
#include "shared/audio.hpp"

extern "C" void __cdecl free(void *block);
void __cdecl operator delete(void *block);

int __fastcall Audio_DS_Channel_Close(AudioChannel *channel)
{
    AudioChannelBuffer *record = channel->DriverBuffer;
    if (record != 0) {
        if (record->Input != 0) {
            free(record->Input);
            record->Input = 0;
            record->InputCapacity = 0;
        }
        if (record->Output != 0) {
            free(record->Output);
            record->Output = 0;
            record->OutputCapacity = 0;
        }
        if (record->Buffer != 0) {
            record->Buffer->Release();
            record->Buffer = 0;
        }
        operator delete(record);
        channel->DriverBuffer = 0;
    }
    return 0;
}
