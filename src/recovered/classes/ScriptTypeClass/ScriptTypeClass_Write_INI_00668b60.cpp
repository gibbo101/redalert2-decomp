// bool ScriptTypeClass::Write_INI(CCINIClass &ini) const (0x00668B60)
// Writes the lines in use ("%d,%d") and clears the rest of "0=" .. "49=".
#include "shared/script.hpp"
// @ref ?Write_INI@AbstractTypeClass@@UBE_NAAVCCINIClass@@@Z=00410910
// @ref ?Build_INI_Entry@ScriptMissionClass@@QBEHPAD@Z=006eafa0
// @ref ??_C@_02MECO@?$CFd?$AA@=007ce9bc

bool ScriptTypeClass::Write_INI(CCINIClass &ini) const
{
    char entry[16];
    char buffer[128];

    if (AbstractTypeClass::Write_INI(ini)) {
        for (int index = 0; index < 50; index++) {
            sprintf(entry, "%d", index);
            strtrim(entry);
            if (index < MissionCount) {
                MissionList[index].Build_INI_Entry(buffer);
                ini.Put_String(ID, entry, buffer);
            } else {
                ini.Clear(ID, entry);
            }
        }
        return true;
    }
    return false;
}
