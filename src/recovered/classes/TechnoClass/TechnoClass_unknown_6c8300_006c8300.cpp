// void TechnoClass::unknown_6c8300() (0x006C8300)
// Restarts the reload timer (+0x194) while below the type's Ammo:
// EmptyReload when empty (if set), else Reload plus ReloadIncrement times
// the square of the full PipWrap groups loaded.
#include "shared/techno.hpp"
// @ref ?Frame@@3HA=00a40d2c

void TechnoClass::unknown_6c8300()
{
    int ammo = unknown_slot32()->Ammo;
    if (unknown_254 < ammo) {
        if (unknown_254 == 0 && unknown_slot32()->EmptyReload != -1) {
            unknown_194 = CDTimerClass<FrameTimerClass>(unknown_slot32()->EmptyReload);
        } else {
            int groups = unknown_slot32()->PipWrap == 0 ? 1 : unknown_254 / unknown_slot32()->PipWrap;
            int delay = unknown_slot32()->ReloadIncrement * groups * groups;
            unknown_194 = CDTimerClass<FrameTimerClass>(unknown_slot32()->Reload + delay);
        }
    }
}
