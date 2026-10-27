// void __fastcall Audio_Stream_Hold(AudioStreamPlayer *stream) -- 0x00407EA0
// Purpose: counts one more hold on the stream.
#include "shared/audio.hpp"

void __fastcall Audio_Stream_Hold(AudioStreamPlayer *stream)
{
    stream->HoldCount++;
}
