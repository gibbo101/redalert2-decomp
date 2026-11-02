// TaskForceClass::TaskForceClass(TaskForceClass const &that) (0x006B69D0)
// Copies the base type, the group, flag and the entries in use.
#include "shared/task_force.hpp"

TaskForceClass::TaskForceClass(TaskForceClass const &that) :
    AbstractTypeClass(that)
{
    Group = that.Group;
    CountEntries = that.CountEntries;
    IsGlobal = that.IsGlobal;
    for (int index = 0; index < CountEntries; index++) {
        Entries[index] = that.Entries[index];
    }
}
