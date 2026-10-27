// AbstractClass *BuildingClass::unknown_slot219(int arg1, CoordStruct const *coord, bool arg3) (0x00442650, slot 219)
// Adds the projectile flags of both weapons (0x00733A60) and flag 1 to
// arg1, then the techno behaviour.
#include "shared/building.hpp"
// @ref ?unknown_func_733a60@WeaponTypeClass@@QBEHXZ=00733a60
// @ref ?unknown_slot219@TechnoClass@@UAEPAVAbstractClass@@HPBUCoordStruct@@_N@Z=006c6530

AbstractClass *BuildingClass::unknown_slot219(int arg1, CoordStruct const *coord, bool arg3)
{
    if (unknown_slot231(0)->WeaponType) {
        arg1 |= unknown_slot231(0)->WeaponType->unknown_func_733a60();
    }
    if (unknown_slot231(1)->WeaponType) {
        arg1 |= unknown_slot231(1)->WeaponType->unknown_func_733a60();
    }
    return TechnoClass::unknown_slot219(arg1 | 1, coord, arg3);
}
