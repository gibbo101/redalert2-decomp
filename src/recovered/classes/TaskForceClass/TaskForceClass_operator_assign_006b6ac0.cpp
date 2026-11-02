// TaskForceClass TaskForceClass::operator=(TaskForceClass const &that) (0x006B6AC0)
// Copies the group, flag and entries (not the type's names) and returns a
// copy of the result by value.
#include "shared/task_force.hpp"

TaskForceClass TaskForceClass::operator=(TaskForceClass const &that)
{
    if (this != &that) {
        Group = that.Group;
        CountEntries = that.CountEntries;
        IsGlobal = that.IsGlobal;
        for (int index = 0; index < CountEntries; index++) {
            Entries[index] = that.Entries[index];
        }
    }
    return *this;
}
