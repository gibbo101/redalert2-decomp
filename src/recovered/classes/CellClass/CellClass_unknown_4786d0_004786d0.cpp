// bool CellClass::unknown_4786d0(int value) (0x004786D0): when flag 0x10 of
// +0x140 is clear and unknown_478760(1, false, false, -1, 0, -1, 1) agrees,
// sets the flag, stores value at +0x50 and answers true.
#include "shared/cell.hpp"

bool CellClass::unknown_4786d0(int value)
{
    if ((unknown_140 & 0x10) == 0 && unknown_478760(1, 0, 0, -1, 0, -1, 1)) {
        unknown_140 |= 0x10;
        unknown_50 = value;
        return true;
    }
    return false;
}
