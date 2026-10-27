// bool ScriptTypeClass::Read_INI(CCINIClass &ini) (0x00668C10)
// Reads the lines "0=" .. "49=" ("%d,%d"), keeping at most 50.
#include "shared/script.hpp"
// @ref ?Read_INI@AbstractTypeClass@@UAE_NAAVCCINIClass@@@Z=004107e0
// @ref ?Read_INI_Entry@ScriptMissionClass@@QAEXPBD@Z=006eaf60
// @ref ??_C@_02MECO@?$CFd?$AA@=007ce9bc
// @ref ??_C@_00A@?$AA@=0083c55c

bool ScriptTypeClass::Read_INI(CCINIClass &ini)
{
    char entry[16];
    char buffer[128];

    if (AbstractTypeClass::Read_INI(ini)) {
        MissionCount = 0;
        for (int index = 0; index < 50; index++) {
            sprintf(entry, "%d", index);
            strtrim(entry);
            if (ini.Get_String(ID, entry, "", buffer, sizeof(buffer)) > 0) {
                ScriptMissionClass mission;
                mission.Read_INI_Entry(buffer);
                if (MissionCount < 50) {
                    MissionList[MissionCount] = mission;
                    MissionCount++;
                }
            }
        }
        return true;
    }
    return false;
}
