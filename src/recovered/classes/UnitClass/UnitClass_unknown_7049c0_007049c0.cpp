// bool UnitClass::unknown_7049c0(int arg1) (0x007049C0)
// Records arg1 at +0x5B4 (-1 means none; a house index, see slot 52) when
// nothing is recorded yet, then calls slot 71 with 2. Answers whether it did.
#include "shared/unit.hpp"

bool UnitClass::unknown_7049c0(int arg1)
{
    if (arg1 != -1 && unknown_5b4 == -1) {
        unknown_5b4 = arg1;
        unknown_slot71(2);
        return true;
    }
    return false;
}
