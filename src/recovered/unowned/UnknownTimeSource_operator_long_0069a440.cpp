// long UnknownTimeSource_0069a440::operator long() const -- 0x0069A440
// Purpose: the same clock as SystemTimerClass (timeGetTime() >> 4, 16 ms
// units); no callers, owner not identified.
#include "shared/system_timer.hpp"
#include "shared/win32_api.hpp"

UnknownTimeSource_0069a440::operator long() const
{
    return timeGetTime() >> 4;
}
