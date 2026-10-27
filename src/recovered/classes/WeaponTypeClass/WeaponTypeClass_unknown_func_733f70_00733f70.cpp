// int WeaponTypeClass::unknown_func_733f70(int range) const (0x00733F70)
// unknown_func_7339c0's value for another range.
#include "shared/weapon_type.hpp"
// @ref ?Rules@@3PAVRulesClass@@A=00839848

int WeaponTypeClass::unknown_func_733f70(int range) const
{
    if (Projectile != 0 && Projectile->ROT == 0) {
        double speed = Projectile->Floater ? Unknown_0047FCD0() : Rules->unknown_1320;
        return Unknown_0047FB70(range, speed);
    }
    return unknown_a8;
}
