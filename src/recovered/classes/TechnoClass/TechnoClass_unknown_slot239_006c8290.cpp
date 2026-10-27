// void TechnoClass::unknown_slot239() (0x006C8290, slot 239)
// Reloads one round (+0x254, up to the type's Ammo) when the +0x194 timer
// has run out, then slot 71 (2) and 0x006C8300.
#include "shared/techno.hpp"
// @ref ?unknown_6c8300@TechnoClass@@QAEXXZ=006c8300
// @ref ?Frame@@3HA=00a40d2c

void TechnoClass::unknown_slot239()
{
    int ammo = unknown_slot32()->Ammo;
    if (ammo != -1 && unknown_254 < ammo && unknown_194.Value() == 0) {
        unknown_254++;
        unknown_slot71(2);
        unknown_6c8300();
    }
}
