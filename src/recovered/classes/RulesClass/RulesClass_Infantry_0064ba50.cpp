// RulesClass::Infantry (0x0064BA50)
// @ref _RulesSection_InfantryTypes=007a9064
// @ref ??_C@_0O@IBPD@InfantryTypes?$AA@=007eec88
// @ref ??_C@_00A@?$AA@=0083c55c
// Makes a InfantryTypeClass for every name listed in [InfantryTypes].
#include "shared/ccini_class.hpp"
#include "shared/rules.hpp"
#include "shared/rules_sections.hpp"
#include "shared/infantry_type.hpp"

bool RulesClass::Infantry(CCINIClass &ini)
{
    int count = ini.Entry_Count(RulesSection_InfantryTypes);
    for (int index = 0; index < count; index++) {
        char buffer[32];
        if (ini.Get_String(RulesSection_InfantryTypes, ini.Get_Entry(RulesSection_InfantryTypes, index), "", buffer, sizeof(buffer))) {
            InfantryTypeClass::Find_Or_Make(buffer);
        }
    }
    return count > 0;
}
