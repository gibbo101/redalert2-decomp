// int TechnoClass::unknown_6d5870() (0x006D5870)
// For an anti-air secondary weapon (slot 230): +0xA4 times the warhead's
// Verses[3] times +0xB4 over +0xB0 (doubled for two-shooter types), / 50.
#include "shared/techno.hpp"
// @ref ?Is_Two_Shooter@TechnoTypeClass@@QBE_NXZ=006daf20

int TechnoClass::unknown_6d5870()
{
    if (unknown_slot163()) {
        WeaponTypeClass *weapon = unknown_slot230()->WeaponType;
        if (weapon->Projectile->AA) {
            double damage = weapon->unknown_a4 * weapon->Warhead->Verses[3];
            int value = (int)(damage * weapon->unknown_b4 / weapon->unknown_b0);
            if (unknown_slot32()->Is_Two_Shooter()) {
                value += value;
            }
            return value / 50;
        }
    }
    return 0;
}
