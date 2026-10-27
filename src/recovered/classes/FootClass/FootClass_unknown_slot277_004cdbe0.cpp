// bool FootClass::unknown_slot277() (0x004CDBE0)
// Clears +0x4C1, then resumes a pending order: with +0x4B8, mission 2 and
// slot 260 on it; else with +0x4BC, mission 1 and slot 220 on it; else
// slot 269 and false.
#include "shared/foot.hpp"

bool FootClass::unknown_slot277()
{
    bool result = true;
    unknown_4c1 = false;
    if (unknown_4b8 != 0) {
        unknown_slot116(2, true);
        unknown_slot260(unknown_4b8, true);
    } else if (unknown_4bc != 0) {
        unknown_slot116(1, true);
        unknown_slot220(unknown_4bc);
    } else {
        unknown_slot269();
        result = false;
    }
    return result;
}
