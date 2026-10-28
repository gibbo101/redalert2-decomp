// bool TechnoClass::unknown_slot96(HouseClass *house) (0x006C2440, slot 96)
// Reveals the object to a house once (+0x373 for the player, +0x374 for the
// others; false when already done or ObjectClass slot 96 refuses). An
// object of a 0x004F52F0-failing house in mission 14 switches to mission 15.
// For the player it also sets the owner's +0x5668/+0x5669 and, unless +0x372,
// springs its tag (event 4) outside game modes 1+ and sets the owner's +0x13C.
#include "shared/techno.hpp"
#include "shared/house.hpp"
#include "shared/tag.hpp"
// @ref ?unknown_player_a35db4@@3PAVHouseClass@@A=00a35db4
// @ref ?unknown_slot96@ObjectClass@@UAE_NPAVHouseClass@@@Z=005d4230
// @ref ?Unknown_004F52F0@HouseClass@@QAE_NXZ=004f52f0
// @ref ?unknown_a40774@@3HA=00a40774
// @ref ?unknown_cell_ac0148@@3VCell@@A=00ac0148
// @ref ?Spring@TagClass@@QAE_NHPAVObjectClass@@VCell@@_NH@Z=006b3df0

bool TechnoClass::unknown_slot96(HouseClass *house)
{
    if (house == unknown_player_a35db4) {
        if (unknown_373) {
            return false;
        }
    } else {
        if (unknown_374) {
            return false;
        }
        unknown_374 = true;
    }
    if (ObjectClass::unknown_slot96(house)) {
        if (!house->Unknown_004F52F0() && unknown_slot91() == 14) {
            unknown_slot116(15, false);
        }
        if (house == unknown_player_a35db4) {
            unknown_373 = true;
            House->unknown_5668 = true;
            House->unknown_5669 = true;
            if (!unknown_372) {
                if (unknown_a40774 == 0 && unknown_34 != 0) {
                    unknown_34->Spring(4, this, unknown_cell_ac0148, 0, 0);
                }
                House->unknown_13c = true;
            }
        } else {
            unknown_374 = true;
        }
        return true;
    }
    return false;
}
