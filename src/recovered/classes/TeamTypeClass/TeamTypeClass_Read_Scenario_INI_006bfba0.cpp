// void TeamTypeClass::Read_Scenario_INI(CCINIClass &ini, int is_global) (0x006BFBA0)
// Creates (or finds) every team type listed in [TeamTypes] and reads its
// own section.
#include "shared/team_type.hpp"
// @ref ??_C@_09GJJE@TeamTypes?$AA@=007f7104
// @ref ??_C@_00A@?$AA@=0083c55c

void __fastcall TeamTypeClass::Read_Scenario_INI(CCINIClass &ini, int is_global)
{
    char buffer[32];

    int count = ini.Entry_Count("TeamTypes");
    for (int index = 0; index < count; index++) {
        char const *entry = ini.Get_Entry("TeamTypes", index);
        ini.Get_String("TeamTypes", entry, "", buffer, sizeof(buffer));
        TeamTypeClass *teamtype = Find_Or_Make(buffer);
        teamtype->Read_INI(ini);
        teamtype->IsGlobal = is_global;
    }
}
