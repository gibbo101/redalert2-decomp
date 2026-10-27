// bool AircraftClass::unknown_slot78(int arg1, int arg2, bool arg3) (0x004174B0, slot 78)
// Acts on slot 28's answer for (arg2, arg3): 2 does nothing, 3, 4 and 17
// go to slot 200 (7, 16 and 2), anything else to FootClass's slot 78 with
// the answer in place of arg1.
#include "shared/aircraft.hpp"
// @ref ?unknown_slot78@FootClass@@UAE_NHH_N@Z=004c61a0

bool AircraftClass::unknown_slot78(int arg1, int arg2, bool arg3)
{
    int action = unknown_slot28((ObjectClass *)arg2, arg3);
    switch (action) {
    case 17:
        return unknown_slot200(2, 0, arg2, 0);

    case 2:
        return false;

    case 3:
        return unknown_slot200(7, 0, arg2, 0);

    case 4:
        return unknown_slot200(16, 0, 0, 0);
    }
    return FootClass::unknown_slot78(action, arg2, arg3);
}
