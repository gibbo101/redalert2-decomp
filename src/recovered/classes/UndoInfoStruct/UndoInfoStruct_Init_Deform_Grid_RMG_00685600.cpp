// void Init_Deform_Grid_RMG_00685600() (0x00685600)
// Builds the deformation grid over the whole map for the random map generator
// (declared by Generate_Hills 0x00584DD0): a corner off the map diamond falls
// back to the first adjacent cell inside it, and a corner is locked unless all
// four cells around it are open. The cell_open 0x006850B0 inline runs out of
// budget at the third corner, which leaves TPoint2D operator+ 0x0042ADD0 and
// the bounds test 0x0058DA10 out of line from there on.
#include "shared/map_view.hpp"
// @ref ?unknown_ramp_corners_7f4174@@3PAPAHA=007f4174
// @ref ?unknown_undo_rows_8286e0@@3HA=008286e0
// @ref ??2@YAPAXI@Z=00782017
// @ref ??AMapClass@@QAEAAVCellClass@@ABVCell@@@Z=00548070
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ??H?$TPoint2D@F@@QBE?BV0@ABV0@@Z=0042add0

extern int *unknown_ramp_corners_7f4174[19];
extern int unknown_undo_rows_8286e0;

void Init_Deform_Grid_RMG_00685600()
{
    if (unknown_undo_cells_abceac != 0) {
        delete unknown_undo_cells_abceac;
        unknown_undo_cells_abceac = 0;
    }
    unknown_undo_cells_abceac = new UnknownUndoCell[(Map.unknown_128 + 1) * (Map.unknown_12c + 1)];
    unknown_undo_width_8286e4 = Map.unknown_128 + 1;
    unknown_undo_rows_8286e0 = Map.unknown_12c + 1;
    unknown_undo_x_8286e8 = Map.unknown_120;
    unknown_undo_y_8286ec = Map.unknown_124;
    Cell offsets[3] = { Cell(0, -1), Cell(-1, -1), Cell(-1, 0) };
    for (int y = 0; y < unknown_undo_rows_8286e0; y++) {
        for (int x = 0; x < unknown_undo_width_8286e4; x++) {
            int value = 0;
            int tries = 0;
            UnknownUndoCell *grid = &unknown_undo_cells_abceac[unknown_undo_width_8286e4 * y + x];
            grid->unknown_04 = 0;
            grid->unknown_05 = 0;
            Cell position(unknown_undo_x_8286e8 + x, unknown_undo_y_8286ec + y);
            Cell cell = position;
            while (!Generation_Cell_In_Bounds_0058da10(cell) && tries < 3) {
                cell = position + offsets[tries];
                tries++;
            }
            if (Generation_Cell_In_Bounds_0058da10(cell)) {
                int ramp = Map[cell].unknown_11c;
                int level = Map[cell].unknown_11b * 15;
                value = *unknown_ramp_corners_7f4174[ramp] + level;
                if (Generation_Cell_In_Bounds_0058da10(position + Cell(0, -1))
                    && !unknown_undo_cell_open_6850b0(&Map[position + Cell(0, -1)], true)) {
                    grid->unknown_04 = 1;
                }
                if (Generation_Cell_In_Bounds_0058da10(position + Cell(-1, -1))
                    && !unknown_undo_cell_open_6850b0(&Map[position + Cell(-1, -1)], true)) {
                    grid->unknown_04 = 1;
                }
                if (Generation_Cell_In_Bounds_0058da10(position + Cell(-1, 0))
                    && !unknown_undo_cell_open_6850b0(&Map[position + Cell(-1, 0)], true)) {
                    grid->unknown_04 = 1;
                }
                if (Generation_Cell_In_Bounds_0058da10(position)
                    && !unknown_undo_cell_open_6850b0(&Map[position], true)) {
                    grid->unknown_04 = 1;
                }
            } else {
                grid->unknown_04 = 1;
            }
            grid->Value = value;
        }
    }
}
