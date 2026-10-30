// int MapClass::Unknown_0054DB10(Pipe &pipe) (0x0054DB10)
// As 0x0054D970 with each cell's +0x119 after its height (TibSun Write_Binary_5).
#include "shared/map.hpp"
#include "shared/map_cell.hpp"
#include "shared/lzo_pipe.hpp"

int MapClass::Unknown_0054DB10(Pipe &pipe)
{
    LZOPipe comp(LZOPipe::COMPRESS, 0x2000);
    comp.Put_To(&pipe);
    int total = 0;

    for (int i = 0; i < Cells.Length(); i++) {
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
                    total += comp.Put(&cellptr->unknown_119, sizeof(cellptr->unknown_119));
                }
            }
        }
    }

    Cell empty = unknown_cell_a6f238;
    total += comp.Put(&empty, sizeof(empty));
    total += comp.End();

    return total;
}
