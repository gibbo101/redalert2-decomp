// void CellClass::unknown_47c8a0() (0x0047C8A0): increments +0x130 (from 0
// when it is -1) up to +0x134, setting flag 0x20 of +0x140 when it becomes
// positive.
#include "shared/cell.hpp"

void CellClass::unknown_47c8a0()
{
    int old = unknown_130;
    if (old == -1) {
        unknown_130 = 0;
    }
    unknown_130++;
    if (unknown_130 > unknown_134) {
        unknown_130 = unknown_134;
    }
    if (old <= 0 && unknown_130 > 0) {
        unknown_140 |= 0x20;
    }
}
