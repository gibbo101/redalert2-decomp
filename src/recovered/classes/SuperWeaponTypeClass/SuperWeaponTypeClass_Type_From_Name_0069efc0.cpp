// int __fastcall SuperWeaponTypeClass::Type_From_Name(char const *name) (0x0069EFC0)
// @ref ?SuperWeaponTypeNames@@3PAPBDA=007f6648
#include "shared/super_weapon_type.hpp"

int __fastcall SuperWeaponTypeClass::Type_From_Name(char const *name)
{
    for (int index = 0; index < 7; index++) {
        if (_stricmp(SuperWeaponTypeNames[index], name) == 0) {
            return index;
        }
    }
    return -1;
}
