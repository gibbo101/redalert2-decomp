// Real independently bounded out-of-line system-clock countdown getter.
// Only this provider uses the declaration guard; caller inline bodies stay unchanged.
#define RA2_CDTIMER_VALUE_SOURCE
#include "shared/system_timer.hpp"
#include "shared/cd_timer.hpp"
// @ref ??BSystemTimerClass@@QBEJXZ=0069a430
template<>
long CDTimerClass<SystemTimerClass>::Value() const
{
    long remain = DelayTime;
    if (Started != 0xFFFFFFFFU) {
        long value = Timer - Started;
        if (value < remain) {
            return remain - value;
        } else {
            return 0;
        }
    }
    return remain;
}

