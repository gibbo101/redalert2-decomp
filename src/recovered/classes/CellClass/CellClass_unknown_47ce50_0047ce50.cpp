// int CellClass::unknown_47ce50() const (0x0047CE50): whether +0xF0 is above
// 1.0.
#include "shared/cell.hpp"

int CellClass::unknown_47ce50() const
{
    if (unknown_f0 > 1.0) {
        return 1;
    }
    return 0;
}
