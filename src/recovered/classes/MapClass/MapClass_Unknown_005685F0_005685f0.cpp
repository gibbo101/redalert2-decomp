// void MapClass::Unknown_005685F0() (0x005685F0)
// Runs CellClass 0x0047BC80 on every cell whose +0x140 bit 1 is clear.
#include "shared/map.hpp"
#include "shared/map_cell.hpp"
// @ref ?unknown_47bc80@CellClass@@QAEXXZ=0047bc80

void MapClass::Unknown_005685F0()
{
    Unknown_0055A550();
    for (CellClass *cell = Unknown_0055A490(); cell != 0; cell = Unknown_0055A490()) {
        if (!(cell->unknown_140 & 2)) {
            cell->unknown_47bc80();
        }
    }
}
