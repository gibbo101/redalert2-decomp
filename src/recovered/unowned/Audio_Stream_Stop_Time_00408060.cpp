// __int64 __fastcall Audio_Stream_Stop_Time(AudioStreamPlayer *stream) -- 0x00408060
// Purpose: the time the stream last stopped playing (+0x20).
#include "shared/audio.hpp"

__int64 __fastcall Audio_Stream_Stop_Time(AudioStreamPlayer *stream)
{
    return stream->unknown_20;
}
