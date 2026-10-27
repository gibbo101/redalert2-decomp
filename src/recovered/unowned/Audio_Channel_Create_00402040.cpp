// AudioChannel *__fastcall Audio_Channel_Create(AudioDevice *device) -- 0x00402040
// Purpose: makes a channel for the device: a zero-filled block with its own
// level sets (Levels, Settings) at neutral, the library's next-piece,
// source-ended and finished handlers, the master levels (0x00830B50) and
// the device's default format, then lets the device's channel driver open
// it. Returns 0 (closing and deleting the channel) when the driver refuses.
// @ref ?Audio_Master_Levels@@3PAUAudioLevelSet@@A=00830b50
#include "shared/crt_memory.hpp"
#include "shared/audio.hpp"

void *__cdecl operator new(unsigned int size);
void __cdecl operator delete(void *block);

AudioChannel *__fastcall Audio_Channel_Create(AudioDevice *device)
{
    AudioChannel *channel = (AudioChannel *)operator new(sizeof(AudioChannel));
    memset(channel, 0, sizeof(AudioChannel));
    Audio_List_Init_Node(channel);
    channel->LoopCount = 0;
    channel->Flags = 0;
    channel->Settings.Init();
    channel->unknown_next_block_15c = Audio_Channel_Next_Piece;
    channel->unknown_end_of_source_160 = Audio_Channel_Source_Ended;
    channel->unknown_stop_callback_164 = Audio_Channel_Finished;
    channel->unknown_next_b0 = 0;
    channel->unknown_loop_b4 = 0;
    channel->unknown_done_b8 = 0;
    channel->unknown_end_callback_bc = 0;
    channel->Owner = 0;
    channel->unknown_0c = 1;
    channel->LoopCount = 0;
    channel->Flags = 0;
    channel->unknown_a0 = 0;
    channel->unknown_levels_94 = Audio_Master_Levels;
    channel->unknown_levels_90 = 0;
    channel->unknown_levels_98 = 0;
    channel->unknown_levels_9c = 0;
    channel->Levels.Init();
    channel->Source = 0;
    channel->Device = device;
    channel->Driver = device->ChannelDriver;
    channel->Format = device->DefaultFormat;
    channel->FormatChanged = 0;
    channel->unknown_1a0 = 0;
    if (device->ChannelDriver->Open(channel) != 0) {
        if (channel != 0) {
            channel->Driver->Close(channel);
            operator delete(channel);
        }
        return 0;
    }
    return channel;
}
