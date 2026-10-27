// void TaskForceClass::Write_Scenario_INI(CCINIClass &ini, int is_global) (0x006B6D10)
// Clears the old [TaskForces] list and its sections, then lists and writes
// every task force whose IsGlobal matches.
#include "shared/task_force.hpp"
// @ref ??_C@_00A@?$AA@=0083c55c
// @ref ??_C@_02MECO@?$CFd?$AA@=007ce9bc
// @ref ??_C@_0L@DFCE@TaskForces?$AA@=007f6da0

void __fastcall TaskForceClass::Write_Scenario_INI(CCINIClass &ini, int is_global)
{
    char buffer[32];

    int count = ini.Entry_Count("TaskForces");
    for (int index = 0; index < count; index++) {
        char const *entry = ini.Get_Entry("TaskForces", index);
        ini.Get_String("TaskForces", entry, "", buffer, sizeof(buffer));
        ini.Clear(buffer);
    }
    ini.Clear("TaskForces");

    int written = 0;
    for (int tf = 0; tf < TaskForces.Count(); tf++) {
        TaskForceClass *taskforce = TaskForces[tf];
        if (taskforce->IsGlobal == is_global) {
            sprintf(buffer, "%d", written++);
            strtrim(buffer);
            ini.Put_String("TaskForces", buffer, taskforce->ID);
            taskforce->Write_INI(ini);
        }
    }
}
