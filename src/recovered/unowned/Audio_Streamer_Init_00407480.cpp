// int Audio_Streamer_Init() -- 0x00407480
// Purpose: sets up the stream list and lock, the streamer thread's block (one pass a second, the timing
// limits four times that) and starts the streamer thread (4 KB stack, above normal priority); a failed
// priority change is reported. 0 when the thread cannot be created.
#include "shared/audio.hpp"
#include "shared/debug_printf.hpp"
// @ref ?Reset@AudioTimeSpan@@QAEXXZ=00403820
// @ref ?Audio_Streamer_Id@@3KA=00831504
// @ref ??_C@_0DL@CKCP@Unable?5to?5change?5the?5priority?5of@=007ccd50

int __fastcall Audio_Streamer_Init()
{
    char message[0x400];
    Audio_List_Init(&Audio_Stream_List);
    InitializeCriticalSection(&Audio_Stream_Lock);
    Audio_Streamer.Quit = 0;
    Audio_Streamer.Done = 0;
    Audio_Streamer.Started = 0;
    Audio_Streamer.Interval = 1000;
    Audio_Streamer.PassCount = 0;
    Audio_Streamer.Timing.Reset();
    Audio_Streamer.Timing.Set(Audio_Streamer.Interval);
    Audio_Streamer.Timing.Set_08(Audio_Streamer.Interval * 4);
    Audio_Streamer.Timing.Set_20(Audio_Streamer.Interval * 4);
    Audio_Streamer_Handle = CreateThread(0, 0x1000, Audio_Streamer_Proc, &Audio_Streamer, 0, &Audio_Streamer_Id);
    if (Audio_Streamer_Handle == 0) {
        return 0;
    }
    if (!SetThreadPriority(Audio_Streamer_Handle, 2)) {
        FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM, 0, GetLastError(), 0, message, 0x400, 0);
        Debug_Printf("Unable to change the priority of the Streamer Thread - %s\n", message);
    }
    Audio_Streamer_Running = 1;
    Audio_Streamer_Initialized = 1;
    return 1;
}
