// void TechnoClass::unknown_slot82(int arg1) (0x006D86B0, slot 82)
// Restarts the +0x154 timer with arg1 and clears unknown_16c.
#include "shared/techno.hpp"
// @ref ?Frame@@3HA=00a40d2c

void TechnoClass::unknown_slot82(int arg1)
{
    unknown_154 = CDTimerClass<FrameTimerClass>(arg1);
    unknown_16c = 0;
}
