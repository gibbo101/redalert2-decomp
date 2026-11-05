// void __fastcall Resume_Movie_Audio_00412320() (0x00412320)
// Restarts the movie's looping secondary buffer and clears the paused flag.
#include "shared/ahandle.hpp"

void __fastcall Resume_Movie_Audio_00412320()
{
    Ahandle *handle = &_handles[0];

    if (handle->Used == true && handle->SecondaryBufferPtr != 0) {
        EnterCriticalSection(&handle->CriticalSection);
        handle->SecondaryBufferPtr->Play(0, 0, DSBPLAY_LOOPING);
        handle->Flags &= ~AHANDLEF_IS_PAUSED;
        LeaveCriticalSection(&handle->CriticalSection);
    }
}
