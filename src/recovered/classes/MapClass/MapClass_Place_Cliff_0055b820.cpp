// bool MapClass::Place_Cliff(CellClass *cellptr, int region_id) (0x0055B820)
// The cliff pass's per-cell step (TibSun Place_Cliff without the Firestorm crystal cliffs):
// the high-ground mask around the cell picks a cliff piece (inside corners, straight runs with
// random variants, outside corners); the piece becomes the pending tile type (+0x11A4, from
// IsoTileTypes at the cliff set 0x00A52E68), the cursor moves to the cell plus the piece's
// offset (unknown_cells_a6fb50, 0x004994D0) and Pick_Random_Tile_Variant (0x0055D640) places
// it over clear ground. False only when that placement fails and clears its result flag.
#include "shared/map.hpp"
#include "shared/map_view.hpp"
#include "shared/map_cell.hpp"
#include "shared/map_isotile.hpp"
#include "shared/tileset_index.hpp"
// @ref ?Unknown_0055BD70@MapClass@@QAEIPAVCellClass@@@Z=0055bd70
// @ref ?Pick_Random_Tile_Variant@MapClass@@QAE_NHHHHAA_N_N@Z=0055d640
// @ref ?Unknown_004994D0@DisplayClass@@QAE?AVCell@@ABV2@@Z=004994d0

unsigned int __fastcall Map_Random_Range_005797a0(unsigned int minimum, unsigned int maximum);
// unknown_cells_a6fb50 (the cliff piece offsets) is defined by 0x0055B520's source earlier in
// this unit: an extern redeclaration after it would emit an empty dynamic initializer.

bool MapClass::Place_Cliff(CellClass *cellptr, int region_id)
{
    int random6 = Map_Random_Range_005797a0(0, 5);
    unsigned int mask = Unknown_0055BD70(cellptr);

    int variant = -1;
    unsigned int south;
    unsigned int east;
    unsigned int southeast;

    if ((mask & 0xA0) == 0xA0) {
        south = Unknown_0055BD70(&Map[cellptr->Fetch_CellID() + Cell(0, 1)]);
        east = Unknown_0055BD70(&Map[cellptr->Fetch_CellID() + Cell(1, 0)]);
        if ((south & 0x20) != 0 || (east & 0x80) != 0) {
            variant = 34;
        } else {
            variant = random6 % 3 + 9;
        }
    } else if ((mask & 0x82) == 0x82) {
        variant = 39;
    } else if ((mask & 0x0A) == 0x0A) {
        variant = 33;
    } else if ((mask & 0x28) == 0x28) {
        variant = 40;
    }

    if (variant == -1) {
        if ((mask & 0x02) != 0) {
            south = Unknown_0055BD70(&Map[cellptr->Fetch_CellID() + Cell(0, 1)]);
            southeast = Unknown_0055BD70(&Map[cellptr->Fetch_CellID() + Cell(1, 1)]);
            if ((mask & 0x04) != 0 && (mask & 0x18) == 0 && (south & 0x0A) != 0x0A) {
                variant = random6 % 3 + 35;
            } else if ((mask & 0x0C) != 0 || (southeast & 0x02) != 0 || (random6 & 1) == 0) {
                variant = 38;
            } else {
                variant = 1;
            }
        } else if ((mask & 0x20) != 0) {
            south = Unknown_0055BD70(&Map[cellptr->Fetch_CellID() + Cell(0, 1)]);
            if ((mask & 0x10) == 0 || (mask & 0x0C) != 0 || (south & 0x28) == 0x28) {
                variant = 18;
            } else {
                variant = random6 % 3 + 15;
            }
        } else if ((mask & 0x08) != 0) {
            east = Unknown_0055BD70(&Map[cellptr->Fetch_CellID() + Cell(1, 0)]);
            southeast = Unknown_0055BD70(&Map[cellptr->Fetch_CellID() + Cell(1, 1)]);
            if ((mask & 0x04) == 0 || (mask & 0x03) != 0 || (east & 0x0A) == 0x0A) {
                if ((mask & 0x06) != 0 || (southeast & 0x08) != 0 || (random6 & 1) == 0) {
                    variant = 26;
                } else {
                    variant = 21;
                }
            } else {
                variant = random6 % 3 + 23;
            }
        } else if ((mask & 0x80) != 0) {
            east = Unknown_0055BD70(&Map[cellptr->Fetch_CellID() + Cell(1, 0)]);
            if ((mask & 0x01) == 0 || (mask & 0x06) != 0 || (east & 0x82) == 0x82) {
                variant = 8;
            } else {
                variant = random6 % 3 + 5;
            }
        }
    }

    if (variant == -1) {
        if ((mask & 0x01) != 0) {
            variant = 2;
        } else if ((mask & 0x04) != 0) {
            variant = (random6 & 1) + 29;
        } else if ((mask & 0x10) != 0) {
            variant = 22;
        } else if ((mask & 0x40) != 0) {
            variant = random6 % 3 + 12;
        } else {
            return true;
        }
    }

    if (variant > 0) {
        Map.unknown_11a4 = IsoTileTypes[unknown_tileset_a52e68 + variant - 1];
        Cell cell = cellptr->Fetch_CellID();
        Cell const &varcell = unknown_cells_a6fb50[variant - 1];

        Map.Unknown_004994D0(XY_Cell(varcell.X + cell.X, varcell.Y + cell.Y));

        bool result = true;
        if (!Pick_Random_Tile_Variant(0, 0, cellptr->unknown_11b, region_id, result, false) && !result) {
            return false;
        }
    }
    return true;
}
