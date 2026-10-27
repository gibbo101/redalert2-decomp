// void BuildingClass::unknown_slot98(int mode) (0x004437A0)
// Sells the building (mission 0x13; hypothesis: Sell_Back): -1 toggles,
// 0 cancels (nothing unless selling) and 1 starts it (not while selling or
// while unknown_5af is set); the sell sound (the rules' +0x62C) plays for a
// player-controlled owner. A building that cannot be sold (unknown_5b9
// clear) only reacts when it is a firestorm wall: its type's slot 33 for the
// owner, the owner's 0x004F52F0, then slots 52 and 60.
#include "shared/building.hpp"
#include "shared/house.hpp"
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?Unknown_004F52B0@HouseClass@@QAE_NXZ=004f52b0
// @ref ?Unknown_004F52F0@HouseClass@@QAE_NXZ=004f52f0
// @ref ?Unknown_00713DB0@@YIHHMHH@Z=00713db0

void BuildingClass::unknown_slot98(int mode)
{
    if (unknown_5b9) {
        bool sell = false;
        switch (mode) {
        case -1:
            sell = unknown_slot91() != 0x13;
            break;
        case 0:
            if (unknown_slot91() != 0x13) {
                return;
            }
            break;
        case 1:
            if (unknown_slot91() == 0x13) {
                return;
            }
            if (unknown_5af) {
                return;
            }
            sell = true;
            break;
        }
        if (sell) {
            unknown_slot116(0x13, false);
            unknown_slot117();
        }
        if (House->Unknown_004F52B0()) {
            Unknown_00713DB0(Rules->unknown_62c, 1.0f, 0x2000, 0);
        }
    } else if (Type->FirestormWall) {
        Type->unknown_slot33((int)House);
        House->Unknown_004F52F0();
        unknown_slot52();
        unknown_slot60();
    }
}
