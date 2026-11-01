// void Audio_Streams_Stop_Filling() -- 0x00408070
// Purpose: clears AUDIO_STREAM_FILLING on every stream, under the stream lock.
#include "shared/audio.hpp"

void __fastcall Audio_Streams_Stop_Filling()
{
    if (Audio_Streamer_Initialized != 0) {
        AudioStreamPlayer *stream = (AudioStreamPlayer *)Audio_List_First(&Audio_Stream_List);
        EnterCriticalSection(&Audio_Stream_Lock);
        for (; stream != 0; stream = (AudioStreamPlayer *)Audio_List_Next(stream)) {
            stream->Flags &= ~AUDIO_STREAM_FILLING;
        }
        LeaveCriticalSection(&Audio_Stream_Lock);
    }
}
