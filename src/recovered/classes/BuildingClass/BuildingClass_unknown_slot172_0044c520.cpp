// int BuildingClass::unknown_slot172() (0x0044C520, slot 172)
// For a crewed type without the flag at +0x5B0: the type's refund (slot 46)
// divided by a rules step (+0x1164 for owner index 1, else +0x1160; doubled
// with +0x5B3), clamped to 1..5; otherwise 0.
#include "shared/building.hpp"
// @ref ?Rules@@3PAVRulesClass@@A=00839848

int BuildingClass::unknown_slot172()
{
    if (!unknown_5b0 && Type->Crewed) {
        int step = (unknown_114 == 1) ? Rules->unknown_1164 : Rules->unknown_1160;
        if (step) {
            if (unknown_5b3) {
                step += step;
            }
            int count = Type->unknown_slot46(House, false) / step;
            if (count < 1) {
                return 1;
            }
            if (count > 5) {
                return 5;
            }
            return count;
        }
    }
    return 0;
}
