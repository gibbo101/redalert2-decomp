// void UnknownTimed_00732ba0::unknown_start_timer() -- 0x00732BA0
// Purpose: starts the system-clock countdown at +0x10: an unstarted timer
// (Started == -1) takes the current time (SystemTimerClass, 0x0069A430).
// Assumptions: CDTimerClass<SystemTimerClass>::Start expanded in an
// unidentified owner (the timer is at +0x10); /O1 like neighbouring code.
#include "shared/system_timer.hpp"
// @ref ??BSystemTimerClass@@QBEJXZ=0069a430

struct UnknownTimed_00732ba0 {
    char unknown_00[0x10];
    long Started;                           // +0x10
    SystemTimerClass Timer;
    void unknown_start_timer();
};

void UnknownTimed_00732ba0::unknown_start_timer()
{
    if (Started == -1) {
        Started = Timer;
    }
}
