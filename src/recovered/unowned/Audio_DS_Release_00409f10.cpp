// void Audio_DS_Release() -- 0x00409F10
// Purpose: DirectSound driver shutdown: releases the DirectSound object;
// when the mixing thread is running and its user count (floored at 0)
// drops to zero, asks it to quit, waits until it reports done and for its
// handle (up to 5 s), closes the handle and clears the running flag.
// Finally deletes the driver lock.
// @ref ?Audio_DirectSound@@3PAUIDirectSound@@A=008315ac
// @ref ?Audio_Lock@@3UCRITICAL_SECTION@@A=00831590
// @ref ?Audio_Thread@@3UAudioThreadBlock@@A=00831560
// @ref ?Audio_Thread_Running@@3HA=008315a8
// @ref ?Audio_Thread_Users@@3HC=00831588
#include "shared/audio.hpp"

void Audio_DS_Release()
{
    if (Audio_DirectSound != 0) {
        Audio_DirectSound->Release();
        Audio_DirectSound = 0;
    }
    if (Audio_Thread_Running != 0) {
        if (--Audio_Thread_Users < 0) {
            Audio_Thread_Users = 0;
        }
        if (Audio_Thread_Users == 0) {
            Audio_Thread.Quit = 1;
            while (Audio_Thread.Done == 0) {
            }
            WaitForSingleObject(Audio_Thread.Handle, 5000);
            CloseHandle(Audio_Thread.Handle);
            Audio_Thread_Running = 0;
        }
    }
    DeleteCriticalSection(&Audio_Lock);
}
