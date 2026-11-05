// bool __fastcall Ripple_Deform_Points_00686610(Point2D start, int direction, bool forced) (0x00686610)
// Pulls the neighbours of a grid point to within one step (15) of it, recording each moved point
// on the undo list, and recurses from every point it moved. A pinned point out of step, or the
// edge of the grid, stops the operation unless it is forced.
#include "shared/crt_memory.hpp"
// @ref ?unknown_undo_rows_8286e0@@3HA=008286e0

extern int unknown_undo_rows_8286e0;
bool __fastcall Ripple_Deform_Points_00686610(Point2D start, int direction, bool forced)
{
    UnknownUndoCell &origin = unknown_undo_cells_abceac[start.X + start.Y * unknown_undo_width_8286e4];
    int height = origin.Value;
    for (int dy = -1; dy < 2; dy++) {
        for (int dx = -1; dx < 2; dx++) {
            if (!(dx || dy)) continue;
            Point2D point = Point2D(dx, dy) + start;
            if (point.X < 0 || point.Y < 0 || point.X >= unknown_undo_width_8286e4 || point.Y >= unknown_undo_rows_8286e0) {
                if (forced) continue;
                return false;
            }
            UnknownUndoCell &cell = unknown_undo_cells_abceac[point.X + point.Y * unknown_undo_width_8286e4];
            if (!cell.unknown_04 || (forced && cell.unknown_06)) {
                if (abs(cell.Value - height) > 15) {
                    if (direction == 1) {
                        if (cell.Value < height) {
                            unknown_undo_record_684fc0(point, cell.Value);
                            cell.Value = height - 15;
                            cell.unknown_05 = 1;
                        }
                    } else {
                        if (cell.Value > height) {
                            unknown_undo_record_684fc0(point, cell.Value);
                            cell.Value = height + 15;
                            cell.unknown_05 = 1;
                        }
                    }
                    if (!cell.unknown_04) {
                        if (!Ripple_Deform_Points_00686610(point, direction, forced)) {
                            if (!forced) {
                                return false;
                            }
                        }
                    }
                }
            } else {
                if (abs(cell.Value - height) > 15) {
                    return false;
                }
            }
        }
    }
    return true;
}
