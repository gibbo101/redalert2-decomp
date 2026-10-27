// void __fastcall Audio_Stream_Release(AudioStreamPlayer *stream) -- 0x00407EB0
// Purpose: drops one hold on the stream (floored at 0).
#include "shared/audio.hpp"

void __fastcall Audio_Stream_Release(AudioStreamPlayer *stream)
{
    if (--stream->HoldCount < 0) {
        stream->HoldCount = 0;
    }
}
