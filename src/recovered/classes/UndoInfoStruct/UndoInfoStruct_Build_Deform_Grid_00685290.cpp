// void __fastcall Build_Deform_Grid_00685290(bool flag, Cell position) (0x00685290)
// Builds the terrain-deformation grid (0x00ABCEAC, one UnknownUndoCell per map
// cell corner, see 0x00685030) around position: corners within 14 cells take
// the cell's corner height times 15 and are locked unless the four cells
// sharing the corner are free; the corners of position are marked as centre.
#include "shared/map_view.hpp"
// @ref ?unknown_ramp_corners_7f4174@@3PAPAHA=007f4174
// @ref ?unknown_undo_rows_8286e0@@3HA=008286e0
// @ref ??2@YAPAXI@Z=00782017
// @ref ??AMapClass@@QAEAAVCellClass@@ABVCell@@@Z=00548070
// @ref ?Map@@3VMouseClass@@A=008324e0

extern int *unknown_ramp_corners_7f4174[19];
extern int unknown_undo_rows_8286e0;

void __fastcall Build_Deform_Grid_00685290(bool flag, Cell position)
{
    if (unknown_undo_cells_abceac != 0) {
        delete unknown_undo_cells_abceac;
        unknown_undo_cells_abceac = 0;
    }
    unknown_undo_cells_abceac = new UnknownUndoCell[(Map.unknown_128 + 1) * (Map.unknown_12c + 1)];
    unknown_undo_width_8286e4 = Map.unknown_128 + 1;
    unknown_undo_rows_8286e0 = Map.unknown_12c + 1;
    unknown_undo_y_8286ec = Map.unknown_124;
    unknown_undo_x_8286e8 = Map.unknown_120;
    Cell lo = position - Cell(14, 14);
    Cell hi = position + Cell(14, 14);
    lo.X = lo.X < 0 ? 0 : lo.X;
    lo.Y = lo.Y < 0 ? 0 : lo.Y;
    int width = Map.unknown_128 - Map.unknown_120;
    hi.X = width < hi.X ? width : hi.X;
    int height = Map.unknown_12c - Map.unknown_124;
    hi.Y = height < hi.Y ? height : hi.Y;
    for (int y = lo.Y; y <= hi.Y; y++) {
        for (int x = lo.X; x <= hi.X; x++) {
            int value = -1;
            UnknownUndoCell *grid = &unknown_undo_cells_abceac[unknown_undo_width_8286e4 * y + x];
            grid->unknown_04 = 0;
            grid->unknown_05 = 0;
            grid->unknown_06 = 0;
            Cell cell(unknown_undo_x_8286e8 + x, unknown_undo_y_8286ec + y);
            if (cell.X >= Map.unknown_120 && cell.X <= Map.unknown_120 + Map.unknown_128
                && cell.Y >= Map.unknown_124 && cell.Y <= Map.unknown_124 + Map.unknown_12c) {
                int ramp = Map[cell].unknown_11c;
                int level = Map[cell].unknown_11b * 15;
                value = *unknown_ramp_corners_7f4174[ramp] + level;
                if (!unknown_undo_cell_free_685150(&Map[cell], flag)
                    || !unknown_undo_cell_free_685150(&Map[cell - Cell(0, 1)], flag)
                    || !unknown_undo_cell_free_685150(&Map[cell - Cell(1, 1)], flag)
                    || !unknown_undo_cell_free_685150(&Map[cell - Cell(1, 0)], flag)) {
                    grid->unknown_04 = 1;
                }
                if (cell == position || cell - Cell(0, 1) == position
                    || cell - Cell(1, 1) == position || cell - Cell(1, 0) == position) {
                    grid->unknown_06 = 1;
                }
            }
            grid->Value = value;
        }
    }
}
