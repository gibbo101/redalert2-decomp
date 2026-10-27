// RulesClass::Terrains (0x0064BEA0)
// @ref _RulesSection_TerrainTypes=007a9080
// @ref ??_C@_0N@NLE@TerrainTypes?$AA@=007eec20
// @ref ??_C@_00A@?$AA@=0083c55c
// Makes a TerrainTypeClass for every name listed in [TerrainTypes].
#include "shared/ccini_class.hpp"
#include "shared/rules.hpp"
#include "shared/rules_sections.hpp"
#include "shared/terrain_type.hpp"

bool RulesClass::Terrains(CCINIClass &ini)
{
    int count = ini.Entry_Count(RulesSection_TerrainTypes);
    for (int index = 0; index < count; index++) {
        char buffer[32];
        if (ini.Get_String(RulesSection_TerrainTypes, ini.Get_Entry(RulesSection_TerrainTypes, index), "", buffer, sizeof(buffer))) {
            TerrainTypeClass::Find_Or_Make(buffer);
        }
    }
    return count > 0;
}
