// int BuildingClass::unknown_451710() (0x00451710)
// The type's +0x11D8 when positive, else the first of the three upgrades
// (unknown_4c0) whose own value is positive; 0 when none.
#include "shared/building.hpp"

int BuildingClass::unknown_451710()
{
    int value = Type->unknown_11d8;
    if (value > 0) {
        return value;
    }
    for (int index = 0; index < 3; index++) {
        if (unknown_4c0[index] && ((BuildingTypeClass *)unknown_4c0[index])->unknown_11d8 > 0) {
            return ((BuildingTypeClass *)unknown_4c0[index])->unknown_11d8;
        }
    }
    return 0;
}
