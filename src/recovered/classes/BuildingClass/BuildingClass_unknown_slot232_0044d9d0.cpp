// bool BuildingClass::unknown_slot232() (0x0044D9D0, slot 232)
// True when the type, or any of the unknown_5c6 types in unknown_4c0, has
// a turret.
#include "shared/building.hpp"

bool BuildingClass::unknown_slot232()
{
    if (Type->Turret) {
        return true;
    }
    if (unknown_5c6) {
        for (int i = 0; i < unknown_5c6; i++) {
            if (unknown_4c0[i] && unknown_4c0[i]->Turret) {
                return true;
            }
        }
    }
    return false;
}
