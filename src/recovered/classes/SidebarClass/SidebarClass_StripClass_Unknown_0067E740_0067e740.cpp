// void const *SidebarClass::StripClass::Unknown_0067E740(int index) (0x0067E740)
// A super weapon type's sidebar icon, or null for a bad index.
#include "shared/sidebar.hpp"
#include "shared/super_weapon_type.hpp"
// @ref ?SuperWeaponTypes@@3V?$DynamicVectorClass@PAVSuperWeaponTypeClass@@@@A=00a40338

void const *SidebarClass::StripClass::Unknown_0067E740(int index)
{
    if ((unsigned)index < (unsigned)SuperWeaponTypes.Count()) {
        return SuperWeaponTypes[index]->SidebarIcon;
    }
    return 0;
}
