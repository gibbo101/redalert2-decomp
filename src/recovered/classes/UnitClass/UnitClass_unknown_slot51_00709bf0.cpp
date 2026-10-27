// HouseClass *UnitClass::unknown_slot51(bool arg1) (0x00709BF0, slot 51)
// The owner as the player sees it: the real owner for the player's allies
// (unless arg1), otherwise the disguise's house at +0x410.
#include "shared/unit.hpp"
// @ref ?Is_Ally@HouseClass@@QBE_NPBV1@@Z=004e5540
// @ref ?unknown_player_a35db4@@3PAVHouseClass@@A=00a35db4

HouseClass *UnitClass::unknown_slot51(bool arg1)
{
    if (House->Is_Ally(unknown_player_a35db4) && !arg1) {
        return House;
    }
    return (HouseClass *)unknown_410;
}
