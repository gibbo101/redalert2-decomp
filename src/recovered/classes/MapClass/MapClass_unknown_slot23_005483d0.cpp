// void MapClass::unknown_slot23() (0x005483D0, slot 23)
// Clears two members of every cell, deletes all cells, runs 0x00529710 and
// makes sure the cell vector holds 512 x 512 empty slots.
#include "shared/map.hpp"
#include "shared/map_cell.hpp"
// @ref ?Unknown_00529710@@YIXH_N@Z=00529710

void MapClass::unknown_slot23()
{
    int index;
    for (index = 0; index < Cells.Length(); index++) {
        CellClass *cell = Cells[index];
        if (cell != 0) {
            cell->unknown_2c = 0;
            cell->unknown_30 = 0;
        }
    }
    for (index = 0; index < Cells.Length(); index++) {
        if (Cells[index] != 0) {
            delete Cells[index];
            Cells[index] = 0;
        }
    }
    Unknown_00529710(0, true);
    if (Cells.Length() < 0x40000) {
        Cells.Resize(0x40000);
        for (index = 0; index < Cells.Length(); index++) {
            Cells[index] = 0;
        }
    }
}
