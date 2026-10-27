// ObjectTypeClass *InfantryClass::unknown_slot50(bool arg1) (0x00509200, slot 50)
// The type shown: the real type when allied to the player and arg1 is
// clear; otherwise the disguise (+0x40C), or the rules default for the
// player's side (+0xB6C, +0xB70 when the player's +0x130 is set or there is
// no player).
#include "shared/infantry.hpp"
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?unknown_player_a35db4@@3PAVHouseClass@@A=00a35db4
// @ref ?Is_Ally@HouseClass@@QBE_NPBV1@@Z=004e5540

ObjectTypeClass *InfantryClass::unknown_slot50(bool arg1)
{
    if (House->Is_Ally(unknown_player_a35db4) && !arg1) {
        return Type;
    }
    if (unknown_40c != 0) {
        return unknown_40c;
    }
    if (unknown_player_a35db4 != 0 && unknown_player_a35db4->unknown_130 == 0) {
        return Rules->unknown_b6c;
    }
    return Rules->unknown_b70;
}
