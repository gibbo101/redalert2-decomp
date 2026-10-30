// bool MapClass::Unknown_0054DFC0(Straw &straw) (0x0054DFC0)
// Reads tile data from an uncompressed straw (TibSun Read_Binary_3): for each
// cell up to the "no cell" value its tile type (fixed up by 0x00529550), sub
// tile and height; the record of a cell off the map is skipped. The dummy cell
// is rebuilt afterwards.
#include "shared/map.hpp"
#include "shared/map_cell.hpp"
#include "shared/map_isotile.hpp"
#include "shared/straw.hpp"
// @ref ?Unknown_00529550@IsometricTileTypeClass@@SIHH@Z=00529550

bool MapClass::Unknown_0054DFC0(Straw &straw)
{
    Cell cell;
    straw.Get(&cell, sizeof(cell));

    while (cell != unknown_cell_a6f238) {
        CellClass *cellptr = &(*this)[cell];
        if (cellptr != 0 && cellptr != &unknown_dummy_cell_a6f9f8) {
            cellptr->IsoTileIndex = 0xFFFF;
            straw.Get(&cellptr->IsoTileIndex, sizeof(cellptr->IsoTileIndex));
            cellptr->IsoTileIndex = IsometricTileTypeClass::Unknown_00529550(cellptr->IsoTileIndex);
            straw.Get(&cellptr->unknown_11a, sizeof(cellptr->unknown_11a));
            straw.Get(&cellptr->unknown_11b, sizeof(cellptr->unknown_11b));
        } else {
            char tmp[sizeof(cellptr->IsoTileIndex) + sizeof(cellptr->unknown_11a) + sizeof(cellptr->unknown_11b)];
            straw.Get(&tmp, sizeof(tmp));
        }
        cell = unknown_cell_a6f238;
        straw.Get(&cell, sizeof(cell));
    }
    new (&unknown_dummy_cell_a6f9f8) CellClass;
    return true;
}
