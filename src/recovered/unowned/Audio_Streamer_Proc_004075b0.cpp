// DWORD __stdcall Audio_Streamer_Proc(void *parameter) -- 0x004075B0
// Purpose: the streamer thread (its parameter is the thread block
// 0x00831480). Until asked to quit, every interval it ticks its timing
// statistics and, under the stream lock, reads the next part of every
// filling stream's file into its ring (0x00408EA0, flagged by
// 0x00AB663C); a stream stops filling when its file is exhausted or the
// read reports an error or the end. Marks the block done when it ends.
#include "shared/audio.hpp"


DWORD __stdcall Audio_Streamer_Proc(void *parameter)
{
    AudioStreamerThread *block = (AudioStreamerThread *)parameter;
    block->Started = 1;
    block->Done = 0;
    while (block->Quit == 0) {
        block->Timing.Tick(Audio_Now());
        EnterCriticalSection(&Audio_Stream_Lock);
        for (AudioStreamPlayer *stream = (AudioStreamPlayer *)Audio_List_First(&Audio_Stream_List); stream != 0;
             stream = (AudioStreamPlayer *)Audio_List_Next(stream)) {
            if (stream->Flags & AUDIO_STREAM_FILLING) {
                EnterCriticalSection(&Audio_Stream_Lock);
                int read;
                int bytes = stream->Remaining;
                Audio_Stream_In_Read = true;
                int result = Audio_Queue_File(stream->Fill, stream->File, bytes, &read);
                Audio_Stream_In_Read = false;
                stream->Remaining -= read;
                if (stream->Remaining <= 0 || result == 2 || result == 0) {
                    stream->Flags &= ~AUDIO_STREAM_FILLING;
                }
                LeaveCriticalSection(&Audio_Stream_Lock);
            }
        }
        LeaveCriticalSection(&Audio_Stream_Lock);
        Sleep((DWORD)block->Interval);
        block->PassCount++;
    }
    block->Done = 1;
    return 0;
}
