// ArmorType __fastcall Armor_From_Name(char const *name) (0x00733A20)
#include "shared/weapon_type.hpp"

ArmorType __fastcall Armor_From_Name(char const *name)
{
    if (name != 0) {
        for (int armor = 0; armor < 11; armor++) {
            if (!_stricmp(ArmorNames[armor], name)) {
                return (ArmorType)armor;
            }
        }
    }
    return ARMOR_NONE;
}
