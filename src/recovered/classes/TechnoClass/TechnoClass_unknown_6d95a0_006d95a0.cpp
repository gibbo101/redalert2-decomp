// void TechnoClass::unknown_6d95a0(UnknownCellClass *cell) (0x006D95A0)
// Records slot 168's value in +0x400 and adds it for the owner to the cell
// (0x00476B20); 0x006D95D0 takes it back.
#include "shared/techno.hpp"
// @ref ?unknown_476b20@UnknownCellClass@@QAEXHH@Z=00476b20

void TechnoClass::unknown_6d95a0(UnknownCellClass *cell)
{
    if (cell != 0) {
        int value = unknown_slot168();
        unknown_400 = value;
        cell->unknown_476b20(Owner(), value);
    }
}
