// bool MapClass::Unknown_0054DCC0(Straw &straw) (0x0054DCC0)
// Reads the tile data of the first 128 x 128 cells through an LCW straw
// (TibSun Read_Binary_1): every tile type (two bytes, fixed up by
// 0x00529550), then every sub tile, then every height; a cell off the map
// reads into the dummy cell, which is rebuilt afterwards.
#include "shared/map.hpp"
#include "shared/map_cell.hpp"
#include "shared/map_isotile.hpp"
#include "shared/lcw_straw.hpp"
// @ref ?Unknown_00529550@IsometricTileTypeClass@@SIHH@Z=00529550

bool MapClass::Unknown_0054DCC0(Straw &straw)
{
    LCWStraw decomp(LCWStraw::DECOMPRESS, 0x2000);
    decomp.Get_From(&straw);

    int i;

    for (i = 0; i < 0x40000 / 16; i++) {
        CellClass *cellptr = &(*this)[Cell(i % 128, i / 128)];
        if (cellptr != 0) {
            cellptr->IsoTileIndex = 0xFFFF;
            decomp.Get(&cellptr->IsoTileIndex, sizeof(cellptr->IsoTileIndex) / 2);
            cellptr->IsoTileIndex = IsometricTileTypeClass::Unknown_00529550(cellptr->IsoTileIndex);
        } else {
            decomp.Get(&unknown_dummy_cell_a6f9f8.IsoTileIndex, sizeof(unknown_dummy_cell_a6f9f8.IsoTileIndex) / 2);
        }
    }

    for (i = 0; i < 0x40000 / 16; i++) {
        CellClass *cellptr = &(*this)[Cell(i % 128, i / 128)];
        if (cellptr != 0) {
            decomp.Get(&cellptr->unknown_11a, sizeof(cellptr->unknown_11a));
        } else {
            decomp.Get(&unknown_dummy_cell_a6f9f8.unknown_11a, sizeof(unknown_dummy_cell_a6f9f8.unknown_11a));
        }
    }

    for (i = 0; i < 0x40000 / 16; i++) {
        CellClass *cellptr = &(*this)[Cell(i % 128, i / 128)];
        if (cellptr != 0) {
            decomp.Get(&cellptr->unknown_11b, sizeof(cellptr->unknown_11b));
        } else {
            decomp.Get(&unknown_dummy_cell_a6f9f8.unknown_11b, sizeof(unknown_dummy_cell_a6f9f8.unknown_11b));
        }
    }

    new (&unknown_dummy_cell_a6f9f8) CellClass;
    return true;
}
