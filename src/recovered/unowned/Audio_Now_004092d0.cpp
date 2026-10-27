// __int64 Audio_Now() -- 0x004092D0
// Purpose: the current time in milliseconds from the chosen clock, or 0
// before Audio_Timer_Init.
// @ref ?Audio_Clock@@3P6A_JXZA=00831558
#include "shared/audio.hpp"

__int64 Audio_Now()
{
    if (Audio_Clock != 0) {
        return Audio_Clock();
    }
    return 0;
}
