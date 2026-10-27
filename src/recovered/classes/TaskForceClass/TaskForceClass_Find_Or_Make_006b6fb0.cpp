// TaskForceClass *TaskForceClass::Find_Or_Make(char const *name) (0x006B6FB0)
// The task force with this ID, created when missing; null for "<none>" and
// "none".
#include "shared/task_force.hpp"
// @ref ??_C@_04KIKH@none?$AA@=007ce0ec
// @ref ??_C@_06CPHF@?$DMnone?$DO?$AA@=007cdecc
// @ref ??2@YAPAXI@Z=00782017

TaskForceClass *__fastcall TaskForceClass::Find_Or_Make(char const *name)
{
    if (_stricmp("<none>", name) == 0 || _stricmp("none", name) == 0) {
        return 0;
    }
    for (int index = 0; index < TaskForces.Count(); index++) {
        if (_stricmp(TaskForces[index]->ID, name) == 0) {
            return TaskForces[index];
        }
    }
    return new TaskForceClass(name);
}
