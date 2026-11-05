// bool Commit_Deform_Grid_RMG_006863e0() (0x006863E0)
// Writes the deformation grid back to the map: every open cell with a changed corner and a
// corner spread under 16 takes the lowest corner / 15 as its height and the ramp that matches
// its corners; then frees the grid.
#include "shared/cell.hpp"
#include "shared/map_view.hpp"
#include "shared/isometric_tile_type.hpp"
#include "shared/tileset_index.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?unknown_undo_width_8286e4@@3HA=008286e4
// @ref ?unknown_undo_x_8286e8@@3HA=008286e8
// @ref ?unknown_undo_y_8286ec@@3HA=008286ec
// @ref ?unknown_undo_cells_abceac@@3PAUUnknownUndoCell@@A=00abceac
// @ref ?unknown_map_min_a70a1c@@3HA=00a70a1c
// @ref ?unknown_map_max_a70a20@@3HA=00a70a20
// @ref ?IsoTileTypes@@3V?$DynamicVectorClass@PAVIsometricTileTypeClass@@@@A=00a40cd0
// @ref ?unknown_generation_cell_56dba0@@YIPAUUnknownMapGenerationCell@@ABVCell@@@Z=0056dba0
// @ref ?unknown_tileset_a52f00@@3HA=00a52f00
// @ref ?unknown_tileset_a6e018@@3HA=00a6e018
// @ref ?unknown_ramp_corners_7f4174@@3PAPAHA=007f4174
// @ref ??3@YAXPAX@Z=00781d3b

extern int *unknown_ramp_corners_7f4174[19];

bool Commit_Deform_Grid_RMG_006863e0()
{
    Map.Unknown_0055A550();
    CellClass *cell = 0;
    for (;;) {
        cell = Map.Unknown_0055A490();
        if (!cell) {
            break;
        }
        int x = cell->Fetch_CellID().X - unknown_undo_x_8286e8;
        int y = cell->Fetch_CellID().Y - unknown_undo_y_8286ec;
        UnknownUndoCell &point1 = unknown_undo_cells_abceac[x + y * unknown_undo_width_8286e4];
        UnknownUndoCell &point2 = unknown_undo_cells_abceac[x + 1 + y * unknown_undo_width_8286e4];
        UnknownUndoCell &point3 = unknown_undo_cells_abceac[x + 1 + (y + 1) * unknown_undo_width_8286e4];
        UnknownUndoCell &point4 = unknown_undo_cells_abceac[x + (y + 1) * unknown_undo_width_8286e4];
        if (point1.unknown_05 || point2.unknown_05 || point3.unknown_05 || point4.unknown_05) {
            int heights[4];
            heights[0] = point1.Value;
            heights[1] = point2.Value;
            heights[2] = point3.Value;
            heights[3] = point4.Value;
            int lowest = 1000;
            int highest = 0;
            for (int index = 0; index < 4; index++) {
                if (heights[index] < lowest) lowest = heights[index];
                if (heights[index] > highest) highest = heights[index];
            }
            if (highest - lowest > 15) continue;
            if (unknown_undo_cell_open_6850b0(cell, true)) {
                cell->unknown_11b = lowest / 15;
            } else {
                continue;
            }
            for (int j = 0; j < 4; j++) {
                heights[j] -= lowest;
            }
            for (int ramp = 0; ramp < 19; ramp++) {
                int *corners = unknown_ramp_corners_7f4174[ramp];
                if (corners[0] == heights[0] && corners[1] == heights[1]
                    && corners[2] == heights[2] && corners[3] == heights[3]) {
                    cell->unknown_11c = ramp;
                    if (ramp == 0) {
                        cell->IsoTileIndex = unknown_tileset_a52f00;
                    } else {
                        cell->IsoTileIndex = ramp - 1 + unknown_tileset_a6e018;
                    }
                    break;
                }
            }
        }
    }
    delete[] unknown_undo_cells_abceac;
    unknown_undo_cells_abceac = 0;
    return true;
}
