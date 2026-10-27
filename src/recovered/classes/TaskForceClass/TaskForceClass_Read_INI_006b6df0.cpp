// bool TaskForceClass::Read_INI(CCINIClass &ini) (0x006B6DF0)
// Reads the entries "0=" .. "5=" (count,type; entries without a known type
// are dropped) and "Group=".
#include "shared/task_force.hpp"
// @ref ??_C@_00A@?$AA@=0083c55c
// @ref ??_C@_02MECO@?$CFd?$AA@=007ce9bc
// @ref ??_C@_05GGEJ@Group?$AA@=007f6dac
// @ref ?Read_INI@AbstractTypeClass@@UAE_NAAVCCINIClass@@@Z=004107e0
// @ref ??0TaskForceEntryStruct@@QAE@PBD@Z=004b4860

bool TaskForceClass::Read_INI(CCINIClass &ini)
{
    char entry[32];
    char buffer[128];

    if (AbstractTypeClass::Read_INI(ini)) {
        CountEntries = 0;
        for (int index = 0; index < 6; index++) {
            sprintf(entry, "%d", index);
            if (ini.Get_String(ID, entry, "", buffer, sizeof(buffer)) > 0) {
                Entries[CountEntries] = TaskForceEntryStruct(buffer);
                if (Entries[CountEntries].Type != 0) {
                    CountEntries++;
                }
            }
        }
        Group = ini.Get_Int(ID, "Group", Group);
        return true;
    }
    return false;
}
