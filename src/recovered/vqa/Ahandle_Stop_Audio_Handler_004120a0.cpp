// long __cdecl Stop_Audio_Handler(VQAHandleP *) (0x004120A0): releases the secondary buffer and the queued blocks.
#include "shared/ahandle.hpp"

long __cdecl Stop_Audio_Handler(VQAHandleP *vqap)
{
    Ahandle *handle = &_handles[vqap->AudioHandleIndex];

    if (handle->SecondaryBufferPtr != 0) {

        EnterCriticalSection(&handle->CriticalSection);
        handle->SecondaryBufferPtr->Stop();
        handle->SecondaryBufferPtr->Release();
        handle->SecondaryBufferPtr = 0;
        handle->AudioBufReadIndex = 0;
        handle->AudioBufWriteIndex = 0;
        for (int i = 0; i < Ahandle::MAX_BUFFERS; i++) {
            handle->AudioBufInUse[i] = false;
        }

        LeaveCriticalSection(&handle->CriticalSection);
    }
    return AHANDLE_OK;
}
