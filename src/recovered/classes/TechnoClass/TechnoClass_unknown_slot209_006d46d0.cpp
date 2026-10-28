// bool TechnoClass::unknown_slot209(CoordStruct const *coord, int arg2) (0x006D46D0)
// Scans for a target (hypothesis: Westwood's Target_Something_Nearby):
// records the frame (+0x3F4), restarts the +0x148 timer with
// GuardAreaTargetingDelay (mission 11) or NormalTargetingDelay plus 0-2
// frames, drops an unreachable current target (slot 218 results 6, 5 and
// 8), and without a target takes slot 219's pick: DistributedFire types
// spread (0x006D4400), others assign it and, for a techno and an accurate
// projectile, book the expected damage on its +0x70. Whether it has a
// target now.
#include "shared/techno.hpp"
#include "shared/rules.hpp"
#include "shared/weapon_type.hpp"
#include "shared/bullet_type.hpp"
#include "shared/id_source.hpp"
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?Frame@@3HA=00a40d2c
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref ??RRandom2Class@@QAEHHH@Z=006388a0
// @ref ?unknown_6ca6c0@TechnoClass@@QAEHPAV1@PAVWeaponTypeClass@@@Z=006ca6c0
// @ref ?unknown_6d4400@TechnoClass@@QAEXXZ=006d4400

bool TechnoClass::unknown_slot209(CoordStruct const *coord, int arg2)
{
    unknown_3f4 = Frame;
    if (Mission == 11) {
        int random = unknown_id_source_a3d290->Random()(0, 2);
        unknown_148 = Rules->GuardAreaTargetingDelay + random;
    } else {
        int random = unknown_id_source_a3d290->Random()(0, 2);
        unknown_148 = Rules->NormalTargetingDelay + random;
    }
    int method = arg2 & 3;
    if (unknown_228 != 0 && unknown_404) {
        int weapon = unknown_slot174(unknown_228);
        int result = unknown_slot218(unknown_228, weapon, 1);
        if (result == 6 && unknown_238 != 0) {
            unknown_238->unknown_68a4b0();
        } else if (result == 6 || result == 5 || result == 8) {
            unknown_slot220(0);
        }
    }
    if (unknown_228 == 0) {
        AbstractClass *target = unknown_slot219(method, coord, false);
        if (unknown_slot32()->DistributedFire) {
            unknown_6d4400();
        } else {
            if (target != 0) {
                unknown_slot220(target);
            }
            int weapon = unknown_slot174(unknown_228);
            TechnoClass *techno = (TechnoClass *)target;
            if (techno != 0) {
                techno = techno->unknown_14_bit0 ? techno : 0;
            }
            WeaponTypeClass *type = unknown_slot231(weapon)->WeaponType;
            if (techno != 0 && type != 0 && !type->Projectile->Inaccurate) {
                techno->unknown_70 -= unknown_6ca6c0(techno, type);
            }
        }
    }
    return unknown_228 != 0;
}
