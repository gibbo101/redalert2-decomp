// int __fastcall Get_Deformed_Cell_Height_00686c90(CellClass *cell) (0x00686C90)
// The cell's height in the deformation grid: the lowest of its four corners
// (divided by 15) when the cell is open (the 0x006850B0 test written out),
// else the map height. The corner index comes from two Fetch_CellID()
// temporaries; the test copies the coordinates into a named local (frame and
// registers match only this way).
#include "shared/cell.hpp"
// @ref ?unknown_undo_width_8286e4@@3HA=008286e4
// @ref ?unknown_undo_x_8286e8@@3HA=008286e8
// @ref ?unknown_undo_y_8286ec@@3HA=008286ec
// @ref ?unknown_undo_cells_abceac@@3PAUUnknownUndoCell@@A=00abceac
// @ref ?unknown_map_min_a70a1c@@3HA=00a70a1c
// @ref ?unknown_map_max_a70a20@@3HA=00a70a20
// @ref ?IsoTileTypes@@3V?$DynamicVectorClass@PAVIsometricTileTypeClass@@@@A=00a40cd0
// @ref ?unknown_generation_cell_56dba0@@YIPAUUnknownMapGenerationCell@@ABVCell@@@Z=0056dba0

int __fastcall Get_Deformed_Cell_Height_00686c90(CellClass *cell)
{
    int x = cell->Fetch_CellID().X - unknown_undo_x_8286e8;
    int y = cell->Fetch_CellID().Y - unknown_undo_y_8286ec;
    int heights[4];
    heights[0] = unknown_undo_cells_abceac[y * unknown_undo_width_8286e4 + x].Value;
    heights[1] = unknown_undo_cells_abceac[y * unknown_undo_width_8286e4 + x + 1].Value;
    heights[2] = unknown_undo_cells_abceac[(y + 1) * unknown_undo_width_8286e4 + x + 1].Value;
    heights[3] = unknown_undo_cells_abceac[(y + 1) * unknown_undo_width_8286e4 + x].Value;
    int lowest = 1000;
    for (int index = 0; index < 4; index++) {
        if (heights[index] < lowest) {
            lowest = heights[index];
        }
    }
    Cell coords = cell->MapCoords;
    if (coords.Y + coords.X > unknown_map_min_a70a1c
        && coords.X - coords.Y < unknown_map_min_a70a1c
        && coords.Y - coords.X < unknown_map_min_a70a1c
        && coords.Y + coords.X <= unknown_map_max_a70a20
        && cell->OverlayIndex == -1
        && cell->OccupierPtr == 0) {
        if (!unknown_generation_cell_56dba0(cell->Fetch_CellID())->unknown_45[0]) {
            int tile = cell->IsoTileIndex;
            if (tile >= IsoTileTypes.Count() || tile == 0xFFFF || IsoTileTypes[tile]->unknown_2b0) {
                return lowest / 15;
            }
        }
    }
    return cell->unknown_11b;
}
