// int MapClass::Unknown_0054D560(Pipe &pipe) (0x0054D560)
// Writes the tile data of every cell slot through an LCW pipe (TibSun
// Write_Binary_1): every tile type (two bytes), then every sub tile, then
// every height; an empty slot writes the dummy cell's. Returns the bytes put.
#include "shared/map.hpp"
#include "shared/map_cell.hpp"
#include "shared/lcw_pipe.hpp"

int MapClass::Unknown_0054D560(Pipe &pipe)
{
    int total = 0;

    LCWPipe comp(LCWPipe::COMPRESS, 0x2000);
    comp.Put_To(&pipe);

    for (int i = 0; i < Cells.Length(); i++) {
        CellClass *cellptr = Cells[i];
        if (cellptr) {
            total += comp.Put(&cellptr->IsoTileIndex, 2);
        } else {
            total += comp.Put(&unknown_dummy_cell_a6f9f8.IsoTileIndex, 2);
        }
    }

    for (int j = 0; j < Cells.Length(); j++) {
        CellClass *cellptr = Cells[j];
        if (cellptr) {
            total += comp.Put(&cellptr->unknown_11a, 1);
        } else {
            total += comp.Put(&unknown_dummy_cell_a6f9f8.unknown_11a, 1);
        }
    }

    for (int k = 0; k < Cells.Length(); k++) {
        CellClass *cellptr = Cells[k];
        if (cellptr) {
            total += comp.Put(&cellptr->unknown_11b, 1);
        } else {
            total += comp.Put(&unknown_dummy_cell_a6f9f8.unknown_11b, 1);
        }
    }

    return total;
}
