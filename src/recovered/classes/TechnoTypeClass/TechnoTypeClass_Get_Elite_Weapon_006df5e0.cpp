// WeaponStruct *TechnoTypeClass::Get_Elite_Weapon(int index) (0x006DF5E0)
// Elite weapon slot `index`.
#include "shared/techno_type.hpp"
#include "shared/house.hpp"

WeaponStruct *TechnoTypeClass::Get_Elite_Weapon(int index)
{
    return &EliteWeapon[index];
}
