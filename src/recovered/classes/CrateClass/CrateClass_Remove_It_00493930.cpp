// bool CrateClass::Remove_It() -- 0x00493930
// Removes the crate this object tracks (if any) and stops its timer.
#include "shared/crate.hpp"

bool CrateClass::Remove_It()
{
    if (Is_Valid()) {
        Location.Unknown_00493C80();
        Make_Invalid();
        return true;
    }
    return false;
}
