// int __fastcall Audio_Stream_Is_Fading(AudioStreamPlayer *stream) -- 0x00407FF0
// Purpose: 1 while the stream plays and its channel's volume is still
// moving towards its target.
#include "shared/audio.hpp"

int __fastcall Audio_Stream_Is_Fading(AudioStreamPlayer *stream)
{
    if ((stream->Flags & AUDIO_STREAM_PLAYING)
        && stream->Channel->Levels.Volume.Current != stream->Channel->Levels.Volume.Target) {
        return 1;
    }
    return 0;
}
