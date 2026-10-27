// bool __stdcall HoverLocomotionClass::Is_Moving_Now() (0x004FC8D0, ILocomotion 32)
#include "shared/hover_locomotion.hpp"
// @ref __real@8@00000000000000000000=0079b610

bool __stdcall HoverLocomotionClass::Is_Moving_Now()
{
    return Is_Moving() && unknown_48 != 0.0;
}
