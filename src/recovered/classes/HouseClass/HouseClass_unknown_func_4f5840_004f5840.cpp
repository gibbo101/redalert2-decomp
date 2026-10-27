// void HouseClass::unknown_func_4f5840(long delay) (0x004F5840)
// @ref ?Frame@@3HA=00a40d2c
#include "shared/techno.hpp"

void HouseClass::unknown_func_4f5840(long delay)
{
    unknown_1f8 = CDTimerClass<FrameTimerClass>(delay);
    unknown_5669 = true;
}
