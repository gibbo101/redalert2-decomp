// int MapClass::Unknown_0054D810(Pipe &pipe) (0x0054D810)
// As 0x0054D660 straight into the pipe, with one "no cell" value at the end
// (TibSun Write_Binary_3).
#include "shared/map.hpp"
#include "shared/map_cell.hpp"
#include "shared/pipe.hpp"

int MapClass::Unknown_0054D810(Pipe &pipe)
{
    int total = 0;

    for (int i = 0; i < Cells.Length(); i++) {
        CellClass *cellptr = Cells[i];
        if (i != 0 && cellptr) {
            if (Unknown_0054AAB0(cellptr->Fetch_CellID())) {
                if (cellptr->Fetch_CellID() != unknown_cell_a6f238 && cellptr != &unknown_dummy_cell_a6f9f8 &&
                    (cellptr->IsoTileIndex != 0xFFFF || cellptr->unknown_11b > 0)) {
                    Cell cell = cellptr->Fetch_CellID();
                    total += pipe.Put(&cell, sizeof(cell));
                    total += pipe.Put(&cellptr->IsoTileIndex, sizeof(cellptr->IsoTileIndex));
                    total += pipe.Put(&cellptr->unknown_11a, sizeof(cellptr->unknown_11a));
                    total += pipe.Put(&cellptr->unknown_11b, sizeof(cellptr->unknown_11b));
                }
            }
        }
    }

    Cell empty = unknown_cell_a6f238;
    total += pipe.Put(&empty, sizeof(empty));

    return total;
}
