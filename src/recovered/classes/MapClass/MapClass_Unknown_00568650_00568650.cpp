// void MapClass::Unknown_00568650() (0x00568650)
// Runs CellClass 0x0047BE00 on every cell.
#include "shared/map.hpp"
#include "shared/map_cell.hpp"
// @ref ?unknown_47be00@CellClass@@QAEXXZ=0047be00

void MapClass::Unknown_00568650()
{
    Unknown_0055A550();
    for (CellClass *cell = Unknown_0055A490(); cell != 0; cell = Unknown_0055A490()) {
        cell->unknown_47be00();
    }
}
