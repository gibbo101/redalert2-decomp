// int BuildingClass::unknown_449d40() (0x00449D40)
// The power the building supplies: the type's Power, plus its ExtraPower
// when unknown_538 is set, plus the Power of each of the three upgrades in
// unknown_4c0 when unknown_5c6 is not zero; scaled by the health ratio when
// positive and unknown_530 is set. 0 when slot 111 holds.
#include "shared/building.hpp"
// @ref ?Health_Ratio@ObjectClass@@QBENXZ=005d4540
// @ref __ftol=0077f110

int BuildingClass::unknown_449d40()
{
    int power = Type->Power;
    if (unknown_slot111()) {
        return 0;
    }
    if (unknown_538) {
        power += Type->ExtraPower;
    }
    if (unknown_5c6) {
        for (int index = 0; index < 3; index++) {
            if (unknown_4c0[index]) {
                power += ((BuildingTypeClass *)unknown_4c0[index])->Power;
            }
        }
    }
    if (power > 0 && unknown_530) {
        return (int)(Health_Ratio() * power);
    }
    return 0;
}
