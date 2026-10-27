// WeaponStruct *TechnoClass::unknown_slot231(int index) (0x006D8540, slot 231)
// Weapon entry index of the type (the alternate list 0x006DF5E0 while +0x118 says so).
#include "shared/techno.hpp"
// @ref ?Get_Elite_Weapon@TechnoTypeClass@@QAEPAUWeaponStruct@@H@Z=006df5e0
// @ref ?Get_Weapon@TechnoTypeClass@@QAEPAUWeaponStruct@@H@Z=006df5c0
// @ref ?unknown_713420@UnknownTechnoPair@@QBE_NXZ=00713420

WeaponStruct *TechnoClass::unknown_slot231(int index)
{
    if (index == -1) {
        return 0;
    }
    if (unknown_118.unknown_713420()) {
        WeaponStruct *weapon = unknown_slot32()->Get_Elite_Weapon(index);
        if (weapon && weapon->WeaponType) {
            return weapon;
        }
    }
    return unknown_slot32()->Get_Weapon(index);
}
