// long __cdecl Play_Audio_Handler(VQAHandleP *) (0x00412000): resumes a paused buffer; the clock skips the pause.
#include "shared/ahandle.hpp"

long __cdecl Play_Audio_Handler(VQAHandleP *vqap)
{
    Ahandle *handle = &_handles[vqap->AudioHandleIndex];

    long rc;
    if (!handle->Used || handle->SecondaryBufferPtr == 0) {
        return AHANDLE_ERROR;
    }

    EnterCriticalSection(&handle->CriticalSection);

    rc = handle->SecondaryBufferPtr->Play(0, 0, 1);
    if (rc == 0) {
        handle->PauseAdjust = Simple_Timer_Callback_Audio_Handler(0) - handle->LastTimerTick;
        Debug_Printf("Ahandle: PauseAdjust %ld\n", handle->PauseAdjust);
        handle->Flags &= ~AHANDLEF_IS_PAUSED;
        rc = AHANDLE_OK;
    } else {
        rc = AHANDLE_ERROR;
    }
    LeaveCriticalSection(&handle->CriticalSection);

    return rc;
}
