// void TechnoTypeClass::Set_Turret_Weapon(int weapon, int index) (0x006DF690)
#include "shared/techno_type.hpp"
#include "shared/house.hpp"

void TechnoTypeClass::Set_Turret_Weapon(int weapon, int index)
{
    unknown_710[index] = weapon;
}
