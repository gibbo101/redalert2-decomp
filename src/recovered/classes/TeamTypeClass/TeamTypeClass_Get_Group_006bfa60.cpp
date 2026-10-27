// int TeamTypeClass::Get_Group() const (0x006BFA60)
// Group, or the task force's group when Group is -1.
#include "shared/team_type.hpp"
#include "shared/task_force.hpp"

int TeamTypeClass::Get_Group() const
{
    int group = Group;
    if (group != -2 && group == -1 && TaskForce != 0) {
        group = TaskForce->Group;
    }
    return group;
}
