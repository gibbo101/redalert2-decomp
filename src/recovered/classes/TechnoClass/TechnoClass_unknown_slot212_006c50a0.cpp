// bool TechnoClass::unknown_slot212(AbstractClass *target, int weapon) (0x006C50A0, slot 212)
// Whether the weapon can reach target: slot 21 of this raises the origin to
// the target's height, a weapon with +0x110 fires from the centre of its cell,
// then 0x006C4BB0 tests the range.
#include "shared/techno.hpp"
#include "shared/gscreen.hpp"
#include "shared/techno_map.hpp"
// @ref ?unknown_6c4bb0@TechnoClass@@QAE_NPBUCoordStruct@@PAVAbstractClass@@PAVWeaponTypeClass@@@Z=006c4bb0

bool TechnoClass::unknown_slot212(AbstractClass *target, int weapon)
{
    if (target == 0) {
        return true;
    }
    CoordStruct coord = Center_Coord();
    WeaponTypeClass *type = unknown_slot231(weapon)->WeaponType;
    if (type != 0 && type->unknown_110) {
        coord = ((AbstractClass *)&Map[Coord_Cell(Center_Coord())])->Center_Coord();
    }
    if (unknown_slot21()) {
        coord.Z = target->Center_Coord().Z;
    }
    return unknown_6c4bb0(&coord, target, type);
}
