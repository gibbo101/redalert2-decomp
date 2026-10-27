// void __fastcall Audio_Stream_Destroy(AudioStreamPlayer *stream) -- 0x004079C0
// Purpose: unlinks the stream (under the stream lock), stops it, releases
// its queues and ring, frees its channel (0x004024A0), deletes its file
// and deletes it.
#include "shared/raw_file_class.hpp"
#include "shared/audio.hpp"

void __cdecl operator delete(void *block);

void __fastcall Audio_Stream_Destroy(AudioStreamPlayer *stream)
{
    if (stream->Prev != stream) {
        EnterCriticalSection(&Audio_Stream_Lock);
        Audio_List_Remove(stream);
        LeaveCriticalSection(&Audio_Stream_Lock);
    }
    Audio_Stream_Stop(stream);
    if (stream->Fill != 0) {
        Audio_Queue_Release(stream->Fill);
        stream->Fill = 0;
    }
    if (stream->Drain != 0) {
        Audio_Queue_Release(stream->Drain);
        stream->Drain = 0;
    }
    if (stream->Ring != 0) {
        Audio_Ring_Destroy(stream->Ring);
    }
    if (stream->Channel != 0) {
        Audio_Channel_Reset(stream->Channel);
    }
    if (stream->File != 0) {
        delete stream->File;
    }
    operator delete(stream);
}
