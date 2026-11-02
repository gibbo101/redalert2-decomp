// long __cdecl Close_Audio_Handler(VQAHandleP *) (0x00411A60): stops the buffer and the timer, frees the handle.
#include "shared/ahandle.hpp"

long __cdecl Close_Audio_Handler(VQAHandleP *vqap)
{
    Debug_Printf("Closing VQ audio handler\n");

    Ahandle *handle = &_handles[vqap->AudioHandleIndex];

    if (handle->Used == 1) {

        if (handle->SecondaryBufferPtr != 0) {
            Debug_Printf("Stop_Audio_Handler\n");
            Stop_Audio_Handler(vqap);
        }

        Debug_Printf("Calling timeKillEvent\n");
        timeKillEvent(handle->TimerHandle);
        handle->TimerHandle = 0;

        Debug_Printf("Calling timeEndPeriod\n");
        timeEndPeriod(1000 / 60);

        handle->Used = false;

        Debug_Printf("Deleting the critical section object\n");
        DeleteCriticalSection(&handle->CriticalSection);
    }

    Debug_Printf("VQ audio handler closed OK\n");
    return AHANDLE_OK;
}
