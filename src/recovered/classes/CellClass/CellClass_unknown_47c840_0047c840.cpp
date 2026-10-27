// void CellClass::unknown_47c840() (0x0047C840): decrements +0x130 (from 0
// when it is 1); at or below zero sets flags 0x18 of +0x12C unless both are
// set already, in which case it clears flag 0x20 of +0x140.
#include "shared/cell.hpp"

void CellClass::unknown_47c840()
{
    if (unknown_130 == 1) {
        unknown_130 = 0;
    }
    unknown_130--;
    bool both = (unknown_12c & 8) && (unknown_12c & 0x10);
    if (!both) {
        if (unknown_130 <= 0) {
            unknown_12c |= 0x18;
        }
    } else if (unknown_130 <= 0 && (unknown_140 & 0x20) == 0x20) {
        unknown_140 &= ~0x20;
    }
}
