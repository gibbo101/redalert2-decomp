// AbstractClass *UnitClass::unknown_slot219(int arg1, CoordStruct const *coord, bool arg3) (0x00706A10, slot 219)
// Nothing for a computer-owned DeployToFire unit. Unless arg1 already has
// one of the flags 0x1B978, adds the projectile flags (0x00733A60) of the
// current weapon (0x006D83E0/0x006D84A0) or of both weapons; then the foot
// behaviour.
#include "shared/unit.hpp"
// @ref ?Unknown_004F52F0@HouseClass@@QAE_NXZ=004f52f0
// @ref ?unknown_6d83e0@TechnoClass@@QAE_NXZ=006d83e0
// @ref ?unknown_6d84a0@TechnoClass@@QAEHXZ=006d84a0
// @ref ?unknown_func_733a60@WeaponTypeClass@@QBEHXZ=00733a60
// @ref ?unknown_slot219@FootClass@@UAEPAVAbstractClass@@HPBUCoordStruct@@_N@Z=004c8420

AbstractClass *UnitClass::unknown_slot219(int arg1, CoordStruct const *coord, bool arg3)
{
    if (House->Unknown_004F52F0() && Type->DeployToFire) {
        return 0;
    }
    if (!(arg1 & 0x1B978)) {
        if (unknown_6d83e0()) {
            arg1 |= unknown_slot231(unknown_6d84a0())->WeaponType->unknown_func_733a60();
        } else {
            if (unknown_slot231(0)->WeaponType) {
                arg1 |= unknown_slot231(0)->WeaponType->unknown_func_733a60();
            }
            if (unknown_slot231(1)->WeaponType) {
                arg1 |= unknown_slot231(1)->WeaponType->unknown_func_733a60();
            }
        }
    }
    return FootClass::unknown_slot219(arg1, coord, arg3);
}
