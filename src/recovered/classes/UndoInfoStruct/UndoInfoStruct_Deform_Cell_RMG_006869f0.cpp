// bool __fastcall Deform_Cell_RMG_006869f0(Cell position, int direction, bool forced, unsigned corners) (0x006869F0)
// The map generator's Deform_Cell: moves the masked corners on the prepared grid, recording each
// on the undo list; a refused corner restores the recorded points unless forced.
extern int unknown_undo_rows_8286e0;
bool __fastcall Deform_Cell_RMG_006869f0(Cell position, int direction, bool forced, unsigned corners)
{
    unknown_UndoInfoStruct_list_00abce18.Clear();
    int mask = ((corners >> 1) & 4) | ((corners & 4) << 1) | (corners & 3);
    int rx = position.X - unknown_undo_x_8286e8;
    int ry = position.Y - unknown_undo_y_8286ec;
    int bit = 1;
    for (int y = ry; y < ry + 2; y++) {
        for (int x = rx; x < rx + 2; x++) {
            if (bit & mask) {
                UnknownUndoCell &cell = unknown_undo_cells_abceac[unknown_undo_width_8286e4 * y + x];
                if (!cell.unknown_04) {
                    cell.Value += direction * 15;
                    if (cell.Value < 0 || cell.Value > 180) {
                        cell.Value -= direction * 15;
                    } else {
                        unknown_undo_record_684fc0(Point2D(x, y), cell.Value - direction * 15);
                    }
                    cell.unknown_05 = 1;
                    if (!Ripple_Deform_Points_00686610(Point2D(x, y), direction, forced) && !forced) {
                        unknown_undo_restore_685030();
                        return false;
                    }
                } else if (!forced) {
                    unknown_undo_restore_685030();
                    return false;
                }
            }
            bit <<= 1;
        }
    }
    return true;
}
