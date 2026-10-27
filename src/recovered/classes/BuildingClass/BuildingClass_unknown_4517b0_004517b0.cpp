// int BuildingClass::unknown_4517b0() (0x004517B0)
// The type's +0x11E0 when positive, else the first of the three upgrades
// (unknown_4c0) whose own value is positive; 0 when none.
#include "shared/building.hpp"

int BuildingClass::unknown_4517b0()
{
    int value = Type->unknown_11e0;
    if (value > 0) {
        return value;
    }
    for (int index = 0; index < 3; index++) {
        if (unknown_4c0[index] && ((BuildingTypeClass *)unknown_4c0[index])->unknown_11e0 > 0) {
            return ((BuildingTypeClass *)unknown_4c0[index])->unknown_11e0;
        }
    }
    return 0;
}
