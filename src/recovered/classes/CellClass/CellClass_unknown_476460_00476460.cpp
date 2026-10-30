// bool CellClass::unknown_476460(int facing, bool alt) const (0x00476460)
// False for facings 0 and 1; else whether the facing's bit of +0x124 (+0x128
// when alt) is clear. The explicit else keeps the two returns apart (no tail
// merge), as in the original.
#include "shared/cell.hpp"

bool CellClass::unknown_476460(int facing, bool alt) const
{
    if (facing == 0 || facing == 1) {
        return false;
    }
    if (alt) {
        return (unknown_128 & (1 << facing)) == 0;
    } else {
        return (unknown_124 & (1 << facing)) == 0;
    }
}
