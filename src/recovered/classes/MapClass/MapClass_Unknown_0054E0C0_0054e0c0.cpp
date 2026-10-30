// bool MapClass::Unknown_0054E0C0(Straw &straw) (0x0054E0C0)
// As 0x0054DFC0 through an LZO straw (TibSun Read_Binary_4).
#include "shared/map.hpp"
#include "shared/map_cell.hpp"
#include "shared/map_isotile.hpp"
#include "shared/lzo_straw.hpp"
// @ref ?Unknown_00529550@IsometricTileTypeClass@@SIHH@Z=00529550

bool MapClass::Unknown_0054E0C0(Straw &straw)
{
    LZOStraw decomp(LZOStraw::DECOMPRESS, 0x2000);
    decomp.Get_From(&straw);

    Cell cell;
    decomp.Get(&cell, sizeof(cell));

    while (cell != unknown_cell_a6f238) {
        CellClass *cellptr = &(*this)[cell];
        if (cellptr != 0 && cellptr != &unknown_dummy_cell_a6f9f8) {
            cellptr->IsoTileIndex = 0xFFFF;
            decomp.Get(&cellptr->IsoTileIndex, sizeof(cellptr->IsoTileIndex));
            cellptr->IsoTileIndex = IsometricTileTypeClass::Unknown_00529550(cellptr->IsoTileIndex);
            decomp.Get(&cellptr->unknown_11a, sizeof(cellptr->unknown_11a));
            decomp.Get(&cellptr->unknown_11b, sizeof(cellptr->unknown_11b));
        } else {
            char tmp[sizeof(cellptr->IsoTileIndex) + sizeof(cellptr->unknown_11a) + sizeof(cellptr->unknown_11b)];
            decomp.Get(&tmp, sizeof(tmp));
        }
        cell = unknown_cell_a6f238;
        decomp.Get(&cell, sizeof(cell));
    }
    new (&unknown_dummy_cell_a6f9f8) CellClass;
    return true;
}
