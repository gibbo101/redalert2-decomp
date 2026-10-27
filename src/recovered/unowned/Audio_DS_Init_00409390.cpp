// HRESULT __fastcall Audio_DS_Init(AudioDriver *driver) -- 0x00409390
// Purpose: DirectSound driver start-up: initializes the driver lock,
// creates the DirectSound object with priority co-operation on the main
// window, marks the driver ready, and starts the mixing thread (4 KB
// stack, time-critical priority) unless it is running, which only counts
// another user. Returns 0, or 0x80040000 when DirectSound or the thread
// cannot be created. A failed priority change is reported.
// @ref _DirectSoundCreate@12=00781bde
// @ref ??_C@_0DI@PNME@Unable?5to?5change?5the?5priority?5of@=007cd1a0
// @ref ?Audio_DirectSound@@3PAUIDirectSound@@A=008315ac
// @ref ?Audio_Lock@@3UCRITICAL_SECTION@@A=00831590
// @ref ?Audio_Thread@@3UAudioThreadBlock@@A=00831560
// @ref ?Audio_Thread_Proc@@YGKPAX@Z=004094d0
// @ref ?Audio_Thread_Running@@3HA=008315a8
// @ref ?Audio_Thread_Users@@3HC=00831588
#include "shared/audio.hpp"
#include "shared/debug_printf.hpp"

extern HWND MainWindow;                                             // 0x00B263D8

HRESULT __fastcall Audio_DS_Init(AudioDriver *driver)
{
    char message[0x400];
    InitializeCriticalSection(&Audio_Lock);
    if (DirectSoundCreate(0, &Audio_DirectSound, 0) != DS_OK) {
        return 0x80040000;
    }
    Audio_DirectSound->SetCooperativeLevel(MainWindow, DSSCL_PRIORITY);
    driver->unknown_ready_18 = 1;
    if (Audio_Thread_Running == 0) {
        Audio_Thread_Users = 0;
        Audio_Thread.Quit = 0;
        Audio_Thread.Done = 0;
        Audio_Thread.Started = 0;
        Audio_Thread.Interval = 33;
        Audio_Thread.PassCount = 0;
        Audio_Thread.Handle = CreateThread(0, 0x1000, Audio_Thread_Proc, &Audio_Thread, 0, &Audio_Thread.ThreadId);
        if (Audio_Thread.Handle == 0) {
            return 0x80040000;
        }
        Audio_Thread_Users++;
        Audio_Thread_Running = 1;
        if (!SetThreadPriority(Audio_Thread.Handle, THREAD_PRIORITY_TIME_CRITICAL)) {
            FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM, 0, GetLastError(), 0, message, 0x400, 0);
            Debug_Printf("Unable to change the priority of the Audio Thread - %s\n", message);
        }
    } else {
        Audio_Thread_Users++;
    }
    return DS_OK;
}
