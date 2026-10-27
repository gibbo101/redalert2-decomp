// RulesClass::Teams (0x0064BF10)
// @ref _RulesSection_Teams=007a9084
// @ref ??_C@_05HHGK@Teams?$AA@=007eec18
// @ref ??_C@_00A@?$AA@=0083c55c
// Makes (or finds) every team type listed in [TeamTypes] and reads its own section.
#include "shared/ccini_class.hpp"
#include "shared/rules.hpp"
#include "shared/rules_sections.hpp"
#include "shared/team_type.hpp"

bool RulesClass::Teams(CCINIClass &ini)
{
    int count = ini.Entry_Count(RulesSection_Teams);
    for (int index = 0; index < count; index++) {
        char const *entry = ini.Get_Entry(RulesSection_Teams, index);
        char buffer[128];
        TeamTypeClass *team;
        if (ini.Get_String(RulesSection_Teams, entry, "", buffer, sizeof(buffer))) {
            team = TeamTypeClass::Find_Or_Make(buffer);
        } else {
            team = 0;
        }
        team->Read_INI(ini);
    }
    return count > 0;
}
