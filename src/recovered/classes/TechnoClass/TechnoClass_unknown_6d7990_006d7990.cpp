// void TechnoClass::unknown_6d7990() (0x006D7990)
// Restarts the timer at 0x00AC0178 with 25 frames.
#include "shared/techno.hpp"
// @ref ?unknown_timer_ac0178@@3V?$CDTimerClass@VFrameTimerClass@@@@A=00ac0178

void TechnoClass::unknown_6d7990()
{
    unknown_timer_ac0178 = 25;
}
