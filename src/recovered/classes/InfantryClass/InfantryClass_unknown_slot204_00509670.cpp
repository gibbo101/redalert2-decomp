// bool InfantryClass::unknown_slot204() (0x00509670, slot 204)
// Whether on mission 5 or 11 with sequence 0, 9, 10 or 32.
#include "shared/infantry.hpp"

bool InfantryClass::unknown_slot204()
{
    if ((unknown_slot91() == 5 || unknown_slot91() == 11)
        && (Sequence == 0 || Sequence == 9 || Sequence == 10 || Sequence == 32)) {
        return true;
    }
    return false;
}
