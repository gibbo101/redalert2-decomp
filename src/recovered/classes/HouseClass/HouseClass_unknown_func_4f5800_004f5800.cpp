// void HouseClass::unknown_func_4f5800(long delay) (0x004F5800)
// @ref ?Frame@@3HA=00a40d2c
#include "shared/techno.hpp"

void HouseClass::unknown_func_4f5800(long delay)
{
    unknown_1ec = CDTimerClass<FrameTimerClass>(delay);
    unknown_5668 = true;
}
