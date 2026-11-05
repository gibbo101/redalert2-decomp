// bool __fastcall Deform_Cell_00686860(Cell position, int direction, bool forced, unsigned corners) (0x00686860)
// Raises or lowers the masked corners of a cell by one step, ripples the change outward and
// writes the grid back to the map; a refused corner frees the grid unless forced.
// @ref ?Commit_Deform_Grid_00685ac0@@YI_N_NVCell@@@Z=00685ac0
void __fastcall Build_Deform_Grid_00685290(bool flag, Cell position);
bool __fastcall Commit_Deform_Grid_00685ac0(bool forced, Cell position);

bool __fastcall Deform_Cell_00686860(Cell position, int direction, bool forced, unsigned corners)
{
    unknown_UndoInfoStruct_list_00abce18.Clear();
    Build_Deform_Grid_00685290(forced, position);
    int mask = ((corners >> 1) & 4) | ((corners & 4) << 1) | (corners & 3);
    int rx = position.X - unknown_undo_x_8286e8;
    int ry = position.Y - unknown_undo_y_8286ec;
    int bit = 1;
    for (int y = ry; y < ry + 2; y++) {
        for (int x = rx; x < rx + 2; x++) {
            if (bit & mask) {
                UnknownUndoCell &cell = unknown_undo_cells_abceac[unknown_undo_width_8286e4 * y + x];
                if (!cell.unknown_04 || forced) {
                    cell.Value += direction * 15;
                    if (cell.Value < 0 || cell.Value > 180) {
                        cell.Value -= direction * 15;
                    }
                    cell.unknown_05 = 1;
                    if (!Ripple_Deform_Points_00686610(Point2D(x, y), direction, forced) && !forced) {
                        delete[] unknown_undo_cells_abceac;
                        unknown_undo_cells_abceac = 0;
                        return false;
                    }
                } else if (!forced) {
                    delete[] unknown_undo_cells_abceac;
                    unknown_undo_cells_abceac = 0;
                    return false;
                }
            }
            bit <<= 1;
        }
    }
    return Commit_Deform_Grid_00685ac0(forced, position);
}
