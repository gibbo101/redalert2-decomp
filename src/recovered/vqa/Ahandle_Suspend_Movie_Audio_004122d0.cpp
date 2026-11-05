// void __fastcall Suspend_Movie_Audio_004122d0() (0x004122D0)
// Stops the movie's secondary buffer and marks the handle paused.
#include "shared/ahandle.hpp"

void __fastcall Suspend_Movie_Audio_004122d0()
{
    Ahandle *handle = &_handles[0];

    if (handle->Used == true && handle->SecondaryBufferPtr != 0) {
        EnterCriticalSection(&handle->CriticalSection);
        handle->SecondaryBufferPtr->Stop();
        handle->Flags |= AHANDLEF_IS_PAUSED;
        LeaveCriticalSection(&handle->CriticalSection);
    }
}
