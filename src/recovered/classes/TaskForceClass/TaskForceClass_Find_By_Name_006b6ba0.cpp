// TaskForceClass *TaskForceClass::Find_By_Name(char const *name) (0x006B6BA0)
// The task force whose Name matches name (case-insensitive), or null.
#include "shared/task_force.hpp"

TaskForceClass *__fastcall TaskForceClass::Find_By_Name(char const *name)
{
    if (name != 0) {
        for (int index = 0; index < TaskForces.Count(); index++) {
            if (_stricmp(name, TaskForces[index]->Name) == 0) {
                return TaskForces[index];
            }
        }
    }
    return 0;
}
