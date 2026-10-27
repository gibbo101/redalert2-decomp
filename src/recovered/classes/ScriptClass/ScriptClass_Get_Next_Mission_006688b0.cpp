// ScriptMissionClass ScriptClass::Get_Next_Mission() const (0x006688B0)
// The line after the current one, or (-1, 0) past the end.
#include "shared/script.hpp"

ScriptMissionClass ScriptClass::Get_Next_Mission() const
{
    if (CurrentMission + 1 >= Class->MissionCount) {
        return ScriptMissionClass(-1, 0);
    }
    return Class->MissionList[CurrentMission + 1];
}
