// void unknown_undo_restore_685030() (0x00685030)
// Writes every recorded value back, newest first, into the unit's cell
// table (0x00ABCEAC, eight bytes a cell, row width 0x008286E4), then
// empties the undo list.
// The cell table is the terrain-deformation grid of 0x00685290/0x00685600:
// Value is a corner height times 15, unknown_04 marks a locked corner,
// unknown_05 a changed one and unknown_06 the centre (0x00685290 only). Its
// constructors are the original's: new[] in 0x00685290 clears Value, 04 and
// 05, and 0x00686DD0 copies the corners member by member without 06.
// The grid origin and size (0x008286E0..0x008286EC) are another unit's data.
// @ref ?unknown_undo_cells_abceac@@3PAUUnknownUndoCell@@A=00abceac
// @ref ?unknown_undo_width_8286e4@@3HA=008286e4
// @ref ??3@YAXPAX@Z=00781d3b
struct UnknownUndoCell {
    UnknownUndoCell() : Value(0), unknown_04(0), unknown_05(0) {}
    UnknownUndoCell(UnknownUndoCell const &other) : Value(other.Value), unknown_04(other.unknown_04), unknown_05(other.unknown_05) {}
    int Value;          // +0x00
    char unknown_04;    // +0x04
    char unknown_05;    // +0x05
    char unknown_06;    // +0x06
};
extern UnknownUndoCell *unknown_undo_cells_abceac;
extern int unknown_undo_width_8286e4;
extern int unknown_undo_x_8286e8;
extern int unknown_undo_y_8286ec;

void unknown_undo_restore_685030()
{
    for (int index = unknown_UndoInfoStruct_list_00abce18.Count() - 1; index >= 0; index--) {
        UndoInfoStruct &info = unknown_UndoInfoStruct_list_00abce18[index];
        unknown_undo_cells_abceac[info.Y * unknown_undo_width_8286e4 + info.X].Value = info.Value;
    }
    unknown_UndoInfoStruct_list_00abce18.Clear();
}
