// void __fastcall AudioCountedList::Leave() -- 0x00401F90
// Purpose: counts one user less, never going below 0.
#include "shared/audio.hpp"

void __fastcall AudioCountedList::Leave()
{
    if (--Busy < 0) {
        Busy = 0;
    }
}
