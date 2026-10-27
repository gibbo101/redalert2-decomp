// void __fastcall Audio_Stream_Pause(AudioStreamPlayer *stream) -- 0x00407ED0
// Purpose: counts a pause; the first pauses the channel under the stream
// lock and turns a playing stream into a paused one.
#include "shared/audio.hpp"

void __fastcall Audio_Stream_Pause(AudioStreamPlayer *stream)
{
    if (stream->PauseCount == 0 && stream->Channel != 0) {
        EnterCriticalSection(&Audio_Stream_Lock);
        Audio_Channel_Pause(stream->Channel);
        if (stream->Flags & AUDIO_STREAM_PLAYING) {
            stream->Flags &= ~AUDIO_STREAM_PLAYING;
            stream->Flags |= AUDIO_STREAM_PAUSED;
        }
        LeaveCriticalSection(&Audio_Stream_Lock);
    }
    stream->PauseCount++;
}
