// int AircraftClass::unknown_slot27(Cell const *arg1, bool arg2, bool arg3) (0x00417840, slot 27)
// 0 unless the house allows it (0x004F52B0); FootClass's action, except
// that 5 becomes 0 without a primary weapon.
#include "shared/aircraft.hpp"
// @ref ?Unknown_004F52B0@HouseClass@@QAE_NXZ=004f52b0
// @ref ?unknown_slot27@FootClass@@UAEHPBVCell@@_N1@Z=004cc650

int AircraftClass::unknown_slot27(Cell const *arg1, bool arg2, bool arg3)
{
    if (!House->Unknown_004F52B0()) {
        return 0;
    }
    int action = FootClass::unknown_slot27(arg1, arg2, arg3);
    if (action == 5 && unknown_slot231(0)->WeaponType == 0) {
        action = 0;
    }
    return action;
}
