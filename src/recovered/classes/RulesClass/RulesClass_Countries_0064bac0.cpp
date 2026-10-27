// RulesClass::Countries (0x0064BAC0)
// @ref _RulesSection_Countries=007a9068
// @ref ??_C@_09JMCO@Countries?$AA@=007eec7c
// @ref ??_C@_00A@?$AA@=0083c55c
// Makes a HouseTypeClass for every name listed in [Countries].
#include "shared/ccini_class.hpp"
#include "shared/rules.hpp"
#include "shared/rules_sections.hpp"
#include "shared/house_type.hpp"

bool RulesClass::Countries(CCINIClass &ini)
{
    int count = ini.Entry_Count(RulesSection_Countries);
    for (int index = 0; index < count; index++) {
        char buffer[32];
        if (ini.Get_String(RulesSection_Countries, ini.Get_Entry(RulesSection_Countries, index), "", buffer, sizeof(buffer))) {
            HouseTypeClass::Find_Or_Make(buffer);
        }
    }
    return count > 0;
}
