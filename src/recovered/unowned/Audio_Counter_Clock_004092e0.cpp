// __int64 Audio_Counter_Clock() -- 0x004092E0
// Purpose: the performance counter in milliseconds.
// @ref ?Audio_Ticks_Per_Ms@@3_JA=00831538
// @ref __alldiv=007824d0
#include "shared/audio.hpp"

__int64 Audio_Counter_Clock()
{
    LARGE_INTEGER count;
    QueryPerformanceCounter(&count);
    return count.QuadPart / Audio_Ticks_Per_Ms;
}
