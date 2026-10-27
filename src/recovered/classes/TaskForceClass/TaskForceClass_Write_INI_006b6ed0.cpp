// bool TaskForceClass::Write_INI(CCINIClass &ini) const (0x006B6ED0)
// Writes the entries in use, clears the unused ones, and "Group=".
#include "shared/task_force.hpp"
// @ref ??_C@_02MECO@?$CFd?$AA@=007ce9bc
// @ref ??_C@_05GGEJ@Group?$AA@=007f6dac
// @ref ?Write_INI@AbstractTypeClass@@UBE_NAAVCCINIClass@@@Z=00410910
// @ref ?Text@TaskForceEntryStruct@@QBEPBDXZ=004b4900

bool TaskForceClass::Write_INI(CCINIClass &ini) const
{
    char entry[32];

    if (AbstractTypeClass::Write_INI(ini)) {
        for (int index = 0; index < 6; index++) {
            sprintf(entry, "%d", index);
            if (index < CountEntries) {
                ini.Put_String(ID, entry, Entries[index].Text());
            } else {
                ini.Clear(ID, entry);
            }
        }
        ini.Put_Int(ID, "Group", Group);
        return true;
    }
    return false;
}
