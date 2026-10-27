// bool TaskForceClass::unknown_all_kind16_6b6f70() const (0x006B6F70)
// True when the type of every entry in use reports Kind_Of() == 16.
#include "shared/task_force.hpp"

bool TaskForceClass::unknown_all_kind16_6b6f70() const
{
    for (int index = 0; index < CountEntries; index++) {
        if (Entries[index].Type->Kind_Of() != 16) {
            return false;
        }
    }
    return true;
}
