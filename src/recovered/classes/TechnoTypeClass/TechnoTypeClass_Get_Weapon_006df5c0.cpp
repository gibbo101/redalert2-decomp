// WeaponStruct *TechnoTypeClass::Get_Weapon(int index) (0x006DF5C0)
// Weapon slot `index`.
#include "shared/techno_type.hpp"
#include "shared/house.hpp"

WeaponStruct *TechnoTypeClass::Get_Weapon(int index)
{
    return &Weapon[index];
}
