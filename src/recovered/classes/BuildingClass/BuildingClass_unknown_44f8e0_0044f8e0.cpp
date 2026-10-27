// void BuildingClass::unknown_44f8e0() (0x0044F8E0)
// Brings the building's power-dependent state in line with slot 195 (powered
// or not): a cloak generator sets or clears unknown_5bb, a gap generator
// runs slots 235/236 (and resets +0x1FC/+0x539/+0x200 on power loss), and
// a Powered type with a drain that can toggle runs 0x0044F730 on power
// restored or 0x0044F800 on power lost.
#include "shared/building.hpp"
#include "shared/house.hpp"
// @ref ?unknown_44f730@BuildingClass@@QAEXXZ=0044f730
// @ref ?unknown_44f800@BuildingClass@@QAEXXZ=0044f800

void BuildingClass::unknown_44f8e0()
{
    if (unknown_slot195()) {
        if (Type->CloakGenerator) {
            if (unknown_5bb <= 0) {
                char radius = unknown_5bc;
                if (radius != Type->CloakRadiusInCells) {
                    unknown_5bb = 1;
                    if (radius == Type->CloakRadiusInCells) {
                        unknown_5bc = 0;
                    }
                    unknown_75 = true;
                }
            }
        }
        if (Type->GapGenerator && !unknown_1fd) {
            unknown_slot235();
        }
        if (Type->Powered && Type->PowerDrain_c6c > 0 && Type->TogglePower) {
            unknown_44f730();
        }
    } else {
        if (Type->CloakGenerator && unknown_5bb >= 0 && unknown_5bc != 0) {
            unknown_5bb = -1;
            unknown_75 = true;
        }
        if (Type->GapGenerator && unknown_1fd) {
            unknown_slot236();
            if (unknown_1fc) {
                unknown_1fc = false;
                unknown_539 = false;
                House->unknown_5668 = true;
                unknown_200 = Type->GapRadiusInCells;
                unknown_slot235();
            }
        }
        if (Type->Powered && Type->PowerDrain_c6c > 0 && Type->TogglePower) {
            unknown_44f800();
        }
    }
}
