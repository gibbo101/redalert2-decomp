// bool CellClass::unknown_478720() (0x00478720): undoes unknown_4786d0: when
// flag 0x10 of +0x140 is set, clears it, sets +0x50 to -1 and answers true.
#include "shared/cell.hpp"

bool CellClass::unknown_478720()
{
    if (unknown_140 & 0x10) {
        unknown_50 = -1;
        unknown_140 &= ~0x10;
        return true;
    }
    return false;
}
