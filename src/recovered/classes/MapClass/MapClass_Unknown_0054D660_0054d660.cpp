// int MapClass::Unknown_0054D660(Pipe &pipe) (0x0054D660)
// Writes, through an LCW pipe, the cell, tile type, sub tile and height of
// every cell on the map (0x0054AAB0) that has a tile or height (TibSun
// Write_Binary_2), then the "no cell" value 101 times. Returns the bytes put.
#include "shared/map.hpp"
#include "shared/map_cell.hpp"
#include "shared/lcw_pipe.hpp"

int MapClass::Unknown_0054D660(Pipe &pipe)
{
    int total = 0;

    LCWPipe comp(LCWPipe::COMPRESS, 0x2000);
    comp.Put_To(&pipe);

    int i;
    for (i = 0; i < Cells.Length(); i++) {
        CellClass *cellptr = Cells[i];
        if (i != 0 && cellptr) {
            if (Unknown_0054AAB0(cellptr->Fetch_CellID())) {
                if (cellptr->Fetch_CellID() != unknown_cell_a6f238 && cellptr != &unknown_dummy_cell_a6f9f8 &&
                    (cellptr->IsoTileIndex != 0xFFFF || cellptr->unknown_11b > 0)) {
                    Cell cell = cellptr->Fetch_CellID();
                    total += comp.Put(&cell, sizeof(cell));
                    total += comp.Put(&cellptr->IsoTileIndex, sizeof(cellptr->IsoTileIndex));
                    total += comp.Put(&cellptr->unknown_11a, sizeof(cellptr->unknown_11a));
                    total += comp.Put(&cellptr->unknown_11b, sizeof(cellptr->unknown_11b));
                }
            }
        }
    }

    Cell empty = unknown_cell_a6f238;
    total += comp.Put(&empty, sizeof(empty));
    for (i = 0; i < 100; i++) {
        total += comp.Put(&empty, sizeof(empty));
    }
    comp.End();

    return total;
}
