// TaskForceClass *TaskForceClass::Find_By_ID(char const *name) (0x006B6B50)
// The task force whose ID matches name (case-insensitive), or null.
#include "shared/task_force.hpp"

TaskForceClass *__fastcall TaskForceClass::Find_By_ID(char const *name)
{
    if (name != 0) {
        for (int index = 0; index < TaskForces.Count(); index++) {
            if (_stricmp(name, TaskForces[index]->ID) == 0) {
                return TaskForces[index];
            }
        }
    }
    return 0;
}
