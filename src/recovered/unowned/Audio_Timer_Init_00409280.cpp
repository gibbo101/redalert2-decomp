// void Audio_Timer_Init() -- 0x00409280
// Purpose: picks the millisecond clock: with a performance counter, stores
// its ticks per millisecond and selects the counter clock; otherwise the
// timeGetTime clock.
// @ref ?Audio_Clock@@3P6A_JXZA=00831558
// @ref ?Audio_Counter_Clock@@YA_JXZ=004092e0
// @ref ?Audio_System_Clock@@YA_JXZ=00409310
// @ref ?Audio_Ticks_Per_Ms@@3_JA=00831538
// @ref __alldiv=007824d0
#include "shared/audio.hpp"

void Audio_Timer_Init()
{
    LARGE_INTEGER frequency;
    if (QueryPerformanceFrequency(&frequency)) {
        Audio_Ticks_Per_Ms = frequency.QuadPart / 1000;
        Audio_Clock = Audio_Counter_Clock;
    } else {
        Audio_Clock = Audio_System_Clock;
    }
}
