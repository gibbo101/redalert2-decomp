// void __fastcall Audio_Stream_Stop(AudioStreamPlayer *stream) -- 0x00407E60
// Purpose: unless the stream is held, stops its channel under the stream
// lock.
#include "shared/audio.hpp"

void __fastcall Audio_Stream_Stop(AudioStreamPlayer *stream)
{
    if (stream->HoldCount == 0 && stream->Channel != 0) {
        EnterCriticalSection(&Audio_Stream_Lock);
        Audio_Channel_Stop(stream->Channel);
        LeaveCriticalSection(&Audio_Stream_Lock);
    }
}
