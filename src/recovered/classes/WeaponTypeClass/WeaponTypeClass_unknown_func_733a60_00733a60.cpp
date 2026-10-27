// int WeaponTypeClass::unknown_func_733a60() const (0x00733A60)
// Flags from the projectile type (4 for +0x274, 0xB8 added for +0x275).
#include "shared/weapon_type.hpp"

int WeaponTypeClass::unknown_func_733a60() const
{
    int flags = 0;
    if (Projectile->AA) {
        flags = 4;
    }
    if (Projectile->AG) {
        flags |= 0xB8;
    }
    return flags;
}
