// ScriptMissionClass ScriptClass::Get_Current_Mission() const (0x00668870)
// The current line, or (-1, 0) before the first.
#include "shared/script.hpp"

ScriptMissionClass ScriptClass::Get_Current_Mission() const
{
    if (CurrentMission == -1) {
        return ScriptMissionClass(-1, 0);
    }
    return Class->MissionList[CurrentMission];
}
