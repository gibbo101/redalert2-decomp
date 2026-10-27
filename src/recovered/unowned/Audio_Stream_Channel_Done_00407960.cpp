// int __fastcall Audio_Stream_Channel_Done(AudioChannel *channel) -- 0x00407960
// Purpose: the stream channel's done callback (+0xB8): when the stream was
// playing or paused notes the time, clears its playing, paused and
// filling flags and its pause count. Returns 0.
#include "shared/audio.hpp"

int __fastcall Audio_Stream_Channel_Done(AudioChannel *channel)
{
    AudioStreamPlayer *stream = (AudioStreamPlayer *)channel->Owner;
    if (stream->Flags & (AUDIO_STREAM_PLAYING | AUDIO_STREAM_PAUSED)) {
        stream->unknown_20 = Audio_Now();
    }
    stream->Flags &= ~(AUDIO_STREAM_PLAYING | AUDIO_STREAM_PAUSED | AUDIO_STREAM_FILLING);
    stream->PauseCount = 0;
    return 0;
}
