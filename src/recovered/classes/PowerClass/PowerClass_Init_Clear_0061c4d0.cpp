// void PowerClass::Init_Clear() (0x0061C4D0, slot 7)
// Clears the radar, then restarts the power bar's timers and counters.
#include "shared/power.hpp"
// @ref ?Init_Clear@RadarClass@@UAEXXZ=0062f260
// @ref ??BSystemTimerClass@@QBEJXZ=0069a430

void PowerClass::Init_Clear()
{
    RadarClass::Init_Clear();
    unknown_1538 = -1;
    unknown_153c = -1;
    unknown_150c = CDTimerClass<SystemTimerClass>();
    unknown_1518 = 0;
    unknown_151c = CDTimerClass<SystemTimerClass>();
    unknown_1528 = 0;
    unknown_152c = 0;
    unknown_1530 = 0;
    unknown_1534 = false;
}
