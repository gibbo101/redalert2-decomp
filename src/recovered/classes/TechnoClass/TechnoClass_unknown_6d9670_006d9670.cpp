// void TechnoClass::unknown_6d9670(long delay) (0x006D9670)
// Restarts the +0x148 timer to run for delay frames.
#include "shared/techno.hpp"
// @ref ?Frame@@3HA=00a40d2c

void TechnoClass::unknown_6d9670(long delay)
{
    unknown_148 = CDTimerClass<FrameTimerClass>(delay);
}
