// int __fastcall WeaponTypeClass::Index_From_Name(char const *name) (0x00733F30)
#include "shared/weapon_type.hpp"

int __fastcall WeaponTypeClass::Index_From_Name(char const *name)
{
    for (int index = 0; index < unknown_WeaponTypeClass_list_00839b90.Count(); index++) {
        if (!_stricmp(unknown_WeaponTypeClass_list_00839b90[index]->ID, name)) {
            return index;
        }
    }
    return -1;
}
