// unsigned long ConnectionClass::Time() (0x004815C0)
// The network tick time.
#include "shared/connection.hpp"
// @ref ?TickCount@@3V?$TTimerClass@VSystemTimerClass@@@@A=00839980
// @ref ??BSystemTimerClass@@QBEJXZ=0069a430

unsigned long ConnectionClass::Time()
{
    return TickCount.Time();
}
