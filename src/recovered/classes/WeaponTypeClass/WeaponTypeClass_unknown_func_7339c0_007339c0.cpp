// void WeaponTypeClass::unknown_func_7339c0() (0x007339C0)
// Derives unknown_a8 from the range and the projectile's speed (rules
// default, or 0x0047FCD0 for floaters); nothing for homing (ROT) projectiles.
#include "shared/weapon_type.hpp"
// @ref ?Rules@@3PAVRulesClass@@A=00839848

void WeaponTypeClass::unknown_func_7339c0()
{
    if (Projectile != 0 && Projectile->ROT == 0) {
        double speed = Rules->unknown_1320;
        if (Projectile->Floater) {
            speed = Unknown_0047FCD0();
        }
        unknown_a8 = Unknown_0047FB70(unknown_b4, speed);
    }
}
