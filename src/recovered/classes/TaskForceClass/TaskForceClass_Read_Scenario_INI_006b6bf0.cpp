// void TaskForceClass::Read_Scenario_INI(CCINIClass &ini, int is_global) (0x006B6BF0)
// Creates (or finds) every task force listed in [TaskForces], registers its
// saved ID and reads its own section.
#include "shared/task_force.hpp"
// @ref ??_C@_00A@?$AA@=0083c55c
// @ref ??_C@_04KIKH@none?$AA@=007ce0ec
// @ref ??_C@_06CPHF@?$DMnone?$DO?$AA@=007cdecc
// @ref ??_C@_0L@DFCE@TaskForces?$AA@=007f6da0
// @ref ?Here_I_Am@SwizzleManagerClass@@UAGJJPAX@Z=0069fba0
// @ref ?SwizzleManager@@3VSwizzleManagerClass@@A=00abd868
// @ref ?unknown_hex_to_long_412390@@YIJPBD@Z=00412390

void __fastcall TaskForceClass::Read_Scenario_INI(CCINIClass &ini, int is_global)
{
    char buffer[24];

    int count = ini.Entry_Count("TaskForces");
    for (int index = 0; index < count; index++) {
        char const *entry = ini.Get_Entry("TaskForces", index);
        if (ini.Get_String("TaskForces", entry, "", buffer, sizeof(buffer)) > 0) {
            TaskForceClass *taskforce = Find_Or_Make(buffer);
            SwizzleManager.Here_I_Am(unknown_hex_to_long_412390(buffer), taskforce);
            taskforce->Read_INI(ini);
            taskforce->IsGlobal = is_global;
        }
    }
}
