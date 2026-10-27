// long SystemTimerClass::operator long() const -- 0x0069A430
// Purpose: the system clock in 16 ms units: timeGetTime() >> 4.
#include "shared/system_timer.hpp"
#include "shared/win32_api.hpp"

SystemTimerClass::operator long() const
{
    return timeGetTime() >> 4;
}
