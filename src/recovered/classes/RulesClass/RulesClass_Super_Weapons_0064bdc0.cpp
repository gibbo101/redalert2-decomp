// RulesClass::Super_Weapons (0x0064BDC0)
// @ref _RulesSection_SuperWeaponTypes=007a9078
// @ref ??_C@_0BB@IFII@SuperWeaponTypes?$AA@=007eec40
// @ref ??_C@_00A@?$AA@=0083c55c
// Makes a SuperWeaponTypeClass for every name listed in [SuperWeaponTypes].
#include "shared/ccini_class.hpp"
#include "shared/rules.hpp"
#include "shared/rules_sections.hpp"
#include "shared/super_weapon_type.hpp"

bool RulesClass::Super_Weapons(CCINIClass &ini)
{
    int count = ini.Entry_Count(RulesSection_SuperWeaponTypes);
    for (int index = 0; index < count; index++) {
        char buffer[32];
        if (ini.Get_String(RulesSection_SuperWeaponTypes, ini.Get_Entry(RulesSection_SuperWeaponTypes, index), "", buffer, sizeof(buffer))) {
            SuperWeaponTypeClass::Find_Or_Make(buffer);
        }
    }
    return count > 0;
}
