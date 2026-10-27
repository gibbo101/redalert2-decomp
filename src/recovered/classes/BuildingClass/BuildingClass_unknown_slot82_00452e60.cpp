// void BuildingClass::unknown_slot82(int arg1) (0x00452E60, slot 82)
// Clears the flag at +0x5AF (resetting +0x438 and restarting the timer at
// +0x420), then the techno behaviour.
#include "shared/building.hpp"
// @ref ?unknown_slot82@TechnoClass@@UAEXH@Z=006d86b0
// @ref ?Frame@@3HA=00a40d2c

void BuildingClass::unknown_slot82(int arg1)
{
    if (unknown_5af) {
        unknown_5af = false;
        unknown_420 = CDTimerClass<FrameTimerClass>();
        unknown_438 = 0;
    }
    TechnoClass::unknown_slot82(arg1);
}
