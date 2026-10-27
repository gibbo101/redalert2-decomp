// void __fastcall Audio_Stream_Resume(AudioStreamPlayer *stream) -- 0x00407F20
// Purpose: drops a pause (floored at 0); the last one turns a paused
// stream back into a playing one and resumes its channel under the stream
// lock.
#include "shared/audio.hpp"

void __fastcall Audio_Stream_Resume(AudioStreamPlayer *stream)
{
    if (stream->PauseCount != 0) {
        if (--stream->PauseCount < 0) {
            stream->PauseCount = 0;
        }
        if (stream->PauseCount == 0 && stream->Channel != 0) {
            EnterCriticalSection(&Audio_Stream_Lock);
            if (stream->Flags & AUDIO_STREAM_PAUSED) {
                stream->Flags &= ~AUDIO_STREAM_PAUSED;
                stream->Flags |= AUDIO_STREAM_PLAYING;
            }
            Audio_Channel_Resume(stream->Channel);
            LeaveCriticalSection(&Audio_Stream_Lock);
        }
    }
}
