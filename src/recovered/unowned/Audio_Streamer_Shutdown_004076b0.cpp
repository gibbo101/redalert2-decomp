// void Audio_Streamer_Shutdown() -- 0x004076B0
// Purpose: when the streamer is initialized: stops its thread if it runs
// (asks it to quit, waits until it reports done and for the handle up to
// 5 s, closes it), destroys every stream (stopping each that is not held)
// and deletes the stream lock.
#include "shared/audio.hpp"

void Audio_Streamer_Shutdown()
{
    if (Audio_Streamer_Initialized == 0) {
        return;
    }
    if (Audio_Streamer_Running != 0) {
        Audio_Streamer.Quit = 1;
        while (Audio_Streamer.Done == 0) {
            Sleep(0);
        }
        WaitForSingleObject(Audio_Streamer_Handle, 5000);
        CloseHandle(Audio_Streamer_Handle);
        Audio_Streamer_Running = 0;
    }
    AudioStreamPlayer *stream;
    while ((stream = (AudioStreamPlayer *)Audio_List_First(&Audio_Stream_List)) != 0) {
        Audio_Stream_Stop(stream);
        Audio_Stream_Destroy(stream);
    }
    DeleteCriticalSection(&Audio_Stream_Lock);
    Audio_Streamer_Initialized = 0;
}
