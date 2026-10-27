// ObjectTypeClass *UnitClass::unknown_slot50(bool arg1) (0x00709BB0, slot 50)
// The type as the player sees it: the real type for the player's allies
// (unless arg1), otherwise the disguise at +0x40C.
#include "shared/unit.hpp"
// @ref ?Is_Ally@HouseClass@@QBE_NPBV1@@Z=004e5540
// @ref ?unknown_player_a35db4@@3PAVHouseClass@@A=00a35db4

ObjectTypeClass *UnitClass::unknown_slot50(bool arg1)
{
    if (House->Is_Ally(unknown_player_a35db4) && !arg1) {
        return Type;
    }
    return (ObjectTypeClass *)unknown_40c;
}
