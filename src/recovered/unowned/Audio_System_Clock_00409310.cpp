// __int64 Audio_System_Clock() -- 0x00409310
// Purpose: the timeGetTime clock extended to 64 bits: bumps the reader
// sequence, then (until no other reader interfered) reads timeGetTime,
// counts a wrap of the low word into the high word and stores both.
// Returns the extended time.
// @ref ?Audio_Clock_High@@3QAKA=0079a754
// @ref ?Audio_Clock_Low@@3QAKA=0079a750
// @ref ?Audio_Clock_Sequence@@3HC=0083155c
// @ref ?Audio_Clock_Time@@3_JA=007ccde8
#include "shared/audio.hpp"

__int64 Audio_System_Clock()
{
    int sequence = ++Audio_Clock_Sequence;
    unsigned long high = *Audio_Clock_High;
    unsigned long low = *Audio_Clock_Low;
    while (sequence != Audio_Clock_Sequence) {
        sequence = Audio_Clock_Sequence;
    }
    for (;;) {
        unsigned long now = timeGetTime();
        if (now < low) {
            high++;
        }
        *Audio_Clock_High = high;
        *Audio_Clock_Low = now;
        if (sequence == Audio_Clock_Sequence) {
            break;
        }
        sequence = Audio_Clock_Sequence;
    }
    return Audio_Clock_Time;
}
