// bool InfantryClass::unknown_slot77(int arg1, int arg2, int arg3, bool arg4) (0x00506100, slot 77)
// While deploying, refuses when slot 27 reports cell arg2 as blocked (2);
// otherwise FootClass's slot 77.
#include "shared/infantry.hpp"
// @ref ?unknown_slot77@FootClass@@UAE_NHHH_N@Z=004c69f0

bool InfantryClass::unknown_slot77(int arg1, int arg2, int arg3, bool arg4)
{
    if (unknown_5090d0() && unknown_slot27((Cell const *)arg2, false, arg4) == 2) {
        return false;
    }
    return FootClass::unknown_slot77(arg1, arg2, arg3, arg4);
}
