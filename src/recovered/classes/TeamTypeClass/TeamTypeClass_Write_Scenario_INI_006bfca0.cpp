// void TeamTypeClass::Write_Scenario_INI(CCINIClass &ini, int is_global) (0x006BFCA0)
// Clears the old [TeamTypes] list and its sections, then lists and writes
// every team type whose IsGlobal matches.
#include "shared/team_type.hpp"
// @ref ??_C@_02MECO@?$CFd?$AA@=007ce9bc
// @ref ??_C@_09GJJE@TeamTypes?$AA@=007f7104
// @ref ??_C@_00A@?$AA@=0083c55c

void __fastcall TeamTypeClass::Write_Scenario_INI(CCINIClass &ini, int is_global)
{
    char buffer[32];

    int count = ini.Entry_Count("TeamTypes");
    for (int index = 0; index < count; index++) {
        char const *entry = ini.Get_Entry("TeamTypes", index);
        ini.Get_String("TeamTypes", entry, "", buffer, sizeof(buffer));
        ini.Clear(buffer);
    }
    ini.Clear("TeamTypes");

    int written = 0;
    for (int tt = 0; tt < TeamTypes.Count(); tt++) {
        if (TeamTypes[tt]->IsGlobal == is_global) {
            sprintf(buffer, "%d", written++);
            ini.Put_String("TeamTypes", buffer, TeamTypes[tt]->ID);
            TeamTypes[tt]->Write_INI(ini);
        }
    }
}
