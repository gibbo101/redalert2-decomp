// UnknownFacingDir TechnoClass::unknown_slot170(AbstractClass *target) (0x006CA540, slot 170)
// The firing arc toward target (hypothesis: the ballistic pitch): the
// type's FireAngle without a target; otherwise from the horizontal distance
// and height difference between the line end (0x006D65B0) and the weapon's
// fire coordinate, the weapon's speed (0x00733F70) and the projectile's
// gravity (Rules +0x1320, or 0x0047FCD0 for floaters) through 0x0047F8B0,
// or 0xE000 when that fails.
#include "shared/techno.hpp"
#include "shared/rules.hpp"
#include "shared/weapon_type.hpp"
#include "shared/bullet_type.hpp"
#include "shared/crt_math.hpp"
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref __CIpow=007821b0
// @ref ?unknown_sqrt_4ba410@@YANN@Z=004ba410
// @ref ?Unknown_0047FCD0@@YANXZ=0047fcd0
// @ref ?unknown_func_733f70@WeaponTypeClass@@QBEHH@Z=00733f70
// @ref ?Unknown_0047F8B0@@YI_N_NHHHNPAUUnknownFacingDir@@@Z=0047f8b0
// @ref ?unknown_6d7d20@TechnoClass@@QAE_NH@Z=006d7d20
// @ref ?Has_Turret_Weapons@TechnoTypeClass@@QBE_NXZ=006df680

UnknownFacingDir TechnoClass::unknown_slot170(AbstractClass *target)
{
    UnknownFacingDir dir((unsigned short)(unknown_slot32()->FireAngle << 8));
    if (target != 0) {
        CoordStruct end = unknown_6d65b0();
        int weapon;
        if (unknown_slot32()->Has_Turret_Weapons()) {
            weapon = unknown_10c;
        } else {
            weapon = 0;
        }
        CoordStruct delta = end - unknown_slot181(weapon);
        WeaponTypeClass *type = unknown_slot231(weapon)->WeaponType;
        double speed = Rules->unknown_1320;
        if (type->Projectile != 0 && type->Projectile->Floater) {
            speed = Unknown_0047FCD0();
        }
        int distance = (int)unknown_sqrt_4ba410(pow(delta.X, 2.0) + pow(delta.Y, 2.0));
        int velocity = type->unknown_func_733f70(distance);
        if (!Unknown_0047F8B0(unknown_6d7d20(weapon), velocity, distance, delta.Z, speed, &dir)) {
            dir = UnknownFacingDir(0xE000);
        }
    }
    return dir;
}
