// RulesClass::Buildings (0x0064BE30)
// @ref _RulesSection_BuildingTypes=007a907c
// @ref ??_C@_0O@GBFL@BuildingTypes?$AA@=007eec30
// @ref ??_C@_00A@?$AA@=0083c55c
// Makes a BuildingTypeClass for every name listed in [BuildingTypes].
#include "shared/ccini_class.hpp"
#include "shared/rules.hpp"
#include "shared/rules_sections.hpp"
#include "shared/building_type.hpp"

bool RulesClass::Buildings(CCINIClass &ini)
{
    int count = ini.Entry_Count(RulesSection_BuildingTypes);
    for (int index = 0; index < count; index++) {
        char buffer[32];
        if (ini.Get_String(RulesSection_BuildingTypes, ini.Get_Entry(RulesSection_BuildingTypes, index), "", buffer, sizeof(buffer))) {
            BuildingTypeClass::Find_Or_Make(buffer);
        }
    }
    return count > 0;
}
