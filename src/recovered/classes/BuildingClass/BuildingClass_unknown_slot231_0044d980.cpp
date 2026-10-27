// WeaponStruct *BuildingClass::unknown_slot231(int index) (0x0044D980, slot 231)
// The first weapon at index with a weapon type among the unknown_5c6 types
// in unknown_4c0; otherwise the techno weapon.
#include "shared/building.hpp"
// @ref ?Get_Weapon@TechnoTypeClass@@QAEPAUWeaponStruct@@H@Z=006df5c0
// @ref ?unknown_slot231@TechnoClass@@UAEPAUWeaponStruct@@H@Z=006d8540

WeaponStruct *BuildingClass::unknown_slot231(int index)
{
    if (unknown_5c6) {
        for (int i = 0; i < unknown_5c6; i++) {
            if (unknown_4c0[i]) {
                WeaponStruct *weapon = unknown_4c0[i]->Get_Weapon(index);
                if (weapon->WeaponType) {
                    return weapon;
                }
            }
        }
    }
    return TechnoClass::unknown_slot231(index);
}
