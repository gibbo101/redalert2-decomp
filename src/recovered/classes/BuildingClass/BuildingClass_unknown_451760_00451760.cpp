// int BuildingClass::unknown_451760() (0x00451760)
// The type's +0x11DC when positive, else the first of the three upgrades
// (unknown_4c0) whose own value is positive; 0 when none.
#include "shared/building.hpp"

int BuildingClass::unknown_451760()
{
    int value = Type->unknown_11dc;
    if (value > 0) {
        return value;
    }
    for (int index = 0; index < 3; index++) {
        if (unknown_4c0[index] && ((BuildingTypeClass *)unknown_4c0[index])->unknown_11dc > 0) {
            return ((BuildingTypeClass *)unknown_4c0[index])->unknown_11dc;
        }
    }
    return 0;
}
