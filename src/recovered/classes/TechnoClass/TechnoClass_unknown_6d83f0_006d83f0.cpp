// void TechnoClass::unknown_6d83f0(int index) (0x006D83F0)
// Unless the type has a charge turret, selects turret weapon index (0 when
// outside 0-14): +0x100 the type's turret weapon, +0x10C the index.
#include "shared/techno.hpp"
// @ref ?Get_Turret_Weapon@TechnoTypeClass@@QBEHH@Z=006df6b0

void TechnoClass::unknown_6d83f0(int index)
{
    if (!unknown_slot32()->IsChargeTurret) {
        if (index >= 0 && index < 15) {
            unknown_100 = unknown_slot32()->Get_Turret_Weapon(index);
            unknown_10c = index;
        } else {
            unknown_100 = unknown_slot32()->Get_Turret_Weapon(0);
            unknown_10c = 0;
        }
    }
}
