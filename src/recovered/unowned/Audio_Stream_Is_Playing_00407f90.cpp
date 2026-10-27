// int __fastcall Audio_Stream_Is_Playing(AudioStreamPlayer *stream) -- 0x00407F90
// Purpose: the stream's playing flag.
#include "shared/audio.hpp"

int __fastcall Audio_Stream_Is_Playing(AudioStreamPlayer *stream)
{
    return stream->Flags & AUDIO_STREAM_PLAYING;
}
