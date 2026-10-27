// HouseClass *InfantryClass::unknown_slot51(bool arg1) (0x00509270, slot 51)
// The infantry's house when allied to the player and arg1 is clear;
// otherwise +0x410, or the player's house when that is not set.
#include "shared/infantry.hpp"
// @ref ?unknown_player_a35db4@@3PAVHouseClass@@A=00a35db4
// @ref ?Is_Ally@HouseClass@@QBE_NPBV1@@Z=004e5540

HouseClass *InfantryClass::unknown_slot51(bool arg1)
{
    if (House->Is_Ally(unknown_player_a35db4) && !arg1) {
        return House;
    }
    return unknown_410 != 0 ? unknown_410 : unknown_player_a35db4;
}
