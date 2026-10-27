// int UnitClass::unknown_slot221(int arg1, int arg2) (0x00704ED0, slot 221: Fire)
// arg1 is the target, arg2 the weapon index; answers the bullet. Without a
// weapon nothing. For the primary weapon, notes whether the burst's firing
// sync frame is pending. Unless slot 218 refuses, fires through the techno;
// then reloads when ammunition ran short (not for ManualReload), starts
// the firing animation (FiringFrames * 2 - 1 frames at +0x5A8) when not
// synchronized, updates scalable bullets, and for DisguiseWhenStill types
// restarts the +0x184 timer with the weapon's +0x118 delay.
#include "shared/unit.hpp"
#include "shared/bullet.hpp"
#include "shared/bullet_type.hpp"
// @ref ?unknown_slot221@TechnoClass@@UAEHHH@Z=006ca890
// @ref ?unknown_6c8300@TechnoClass@@QAEXXZ=006c8300
// @ref ?unknown_func_463bc0@BulletClass@@QAEXXZ=00463bc0

int UnitClass::unknown_slot221(int arg1, int arg2)
{
    BulletClass *bullet = 0;
    WeaponTypeClass *weapon = unknown_slot231(arg2)->WeaponType;
    if (!weapon) {
        return 0;
    }
    bool synchronized = false;
    if (arg2 == 0) {
        int burst = unknown_310 % weapon->Burst;
        int frame;
        if (burst < 2) {
            frame = Type->FiringSyncFrame[burst];
        } else {
            frame = -1;
        }
        if (unknown_5a8 != -1 && frame != -1) {
            synchronized = true;
        } else {
            synchronized = false;
        }
    }
    if (!unknown_slot218((AbstractClass *)arg1, arg2, 1)) {
        bullet = (BulletClass *)TechnoClass::unknown_slot221(arg1, arg2);
        if (bullet) {
            if (Type->Ammo > 0 && unknown_254 < Type->Ammo && !Type->ManualReload) {
                unknown_6c8300();
            }
            if (!synchronized && Type->FiringFrames > 0) {
                unknown_5a8 = Type->FiringFrames * 2 - 1;
            }
            if (bullet->Type->Scalable) {
                bullet->unknown_func_463bc0();
            }
            if (Type->DisguiseWhenStill) {
                unknown_184 = CDTimerClass<FrameTimerClass>(weapon->unknown_118);
            }
        }
    }
    return (int)bullet;
}
