// long __cdecl Pause_Audio_Handler(VQAHandleP *) (0x00411FB0)
#include "shared/ahandle.hpp"

long __cdecl Pause_Audio_Handler(VQAHandleP *vqap)
{
    Ahandle *handle = &_handles[vqap->AudioHandleIndex];

    EnterCriticalSection(&handle->CriticalSection);

    if (handle->Used == true && handle->SecondaryBufferPtr != 0) {
        handle->SecondaryBufferPtr->Stop();
    }
    handle->Flags |= AHANDLEF_IS_PAUSED;

    LeaveCriticalSection(&handle->CriticalSection);

    return AHANDLE_OK;
}
