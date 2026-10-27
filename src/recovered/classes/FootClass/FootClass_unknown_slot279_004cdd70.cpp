// bool FootClass::unknown_slot279() (0x004CDD70)
// In state 0x1D: a pending unknown_4c1 or mission 5 runs slot 277,
// otherwise slot 269.
#include "shared/foot.hpp"

bool FootClass::unknown_slot279()
{
    bool result = false;
    if (unknown_4b4 == 0x1D) {
        if (unknown_4c1) {
            unknown_4c1 = false;
            result = unknown_slot277();
        } else if (unknown_slot91() == 5 || unknown_slot91() == 5) {
            result = unknown_slot277();
        } else {
            unknown_slot269();
            result = false;
        }
    }
    return result;
}
