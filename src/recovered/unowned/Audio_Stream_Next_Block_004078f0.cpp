// int __fastcall Audio_Stream_Next_Block(AudioChannel *channel) -- 0x004078F0
// Purpose: the stream channel's next-block callback (+0xB0): advances the
// stream's play queue by the last block, refreshes it, and gives the
// channel the next block (at most the stream's block size, +0xA0) at the
// queue's position. Returns 0.
#include "shared/audio.hpp"

int __fastcall Audio_Stream_Next_Block(AudioChannel *channel)
{
    AudioStreamPlayer *stream = (AudioStreamPlayer *)channel->Owner;
    Audio_Queue_Update(stream->Drain, stream->unknown_90);
    Audio_Queue_Ready(stream->Drain);
    if (stream->unknown_a0 > stream->Drain->Available) {
        stream->unknown_90 = stream->Drain->Available;
    } else {
        stream->unknown_90 = stream->unknown_a0;
    }
    channel->unknown_178 = channel->unknown_174 = stream->unknown_90;
    channel->unknown_170 = (int)stream->Drain->Pointer;
    return 0;
}
