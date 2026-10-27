// void __fastcall Audio_Channel_Reuse(AudioChannel *channel) -- 0x004024A0
// Purpose: gives a free channel (flag 8) a fresh start: clears the flag and
// puts the handlers, counters, levels and source back as 0x00402040 left a
// new channel. Does nothing for a channel that is not free.
// @ref ?Audio_Master_Levels@@3PAUAudioLevelSet@@A=00830b50
#include "shared/audio.hpp"

void __fastcall Audio_Channel_Reuse(AudioChannel *channel)
{
    if (channel->Flags & AUDIO_CHANNEL_FREE) {
        channel->Flags &= ~AUDIO_CHANNEL_FREE;
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
    }
}
