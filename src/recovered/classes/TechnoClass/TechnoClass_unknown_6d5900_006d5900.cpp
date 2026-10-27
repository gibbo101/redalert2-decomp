// int TechnoClass::unknown_6d5900() (0x006D5900)
// For a ground-capable (AG) secondary weapon (slot 230): +0xA4 times the
// warhead's Verses[4] times the range (+0xB4, at most 1024) over +0xB0,
// doubled for two-shooter types and halved for Inaccurate projectiles, / 50.
#include "shared/techno.hpp"
// @ref ?Is_Two_Shooter@TechnoTypeClass@@QBE_NXZ=006daf20

int TechnoClass::unknown_6d5900()
{
    if (unknown_slot163() && unknown_slot230()->WeaponType->Projectile->AG) {
        WeaponTypeClass *weapon = unknown_slot230()->WeaponType;
        int range = weapon->unknown_b4;
        BulletTypeClass *projectile = weapon->Projectile;
        WarheadTypeClass *warhead = weapon->Warhead;
        if (range >= 1024) {
            range = 1024;
        }
        double damage = weapon->unknown_a4 * warhead->Verses[4];
        int value = (int)(damage * range / weapon->unknown_b0);
        if (unknown_slot32()->Is_Two_Shooter()) {
            value += value;
        }
        if (projectile->Inaccurate) {
            value /= 2;
        }
        return value / 50;
    }
    return 0;
}
