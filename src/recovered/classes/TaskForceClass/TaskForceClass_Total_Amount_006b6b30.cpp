// int TaskForceClass::Total_Amount() const (0x006B6B30)
// The number of objects the entries in use ask for.
#include "shared/task_force.hpp"

int TaskForceClass::Total_Amount() const
{
    int total = 0;
    for (int index = 0; index < CountEntries; index++) {
        total += Entries[index].Amount;
    }
    return total;
}
