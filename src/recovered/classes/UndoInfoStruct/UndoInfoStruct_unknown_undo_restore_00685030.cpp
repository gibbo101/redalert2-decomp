// void unknown_undo_restore_685030() (0x00685030)
// Writes every recorded value back, newest first, into the unit's cell
// table (0x00ABCEAC, eight bytes a cell, row width 0x008286E4), then
// empties the undo list.
// @ref ?unknown_undo_cells_abceac@@3PAUUnknownUndoCell@@A=00abceac
// @ref ?unknown_undo_width_8286e4@@3HA=008286e4
// @ref ??3@YAXPAX@Z=00781d3b
struct UnknownUndoCell {
    int Value;          // +0x00
    int unknown_04;     // +0x04
};
extern UnknownUndoCell *unknown_undo_cells_abceac;
extern int unknown_undo_width_8286e4;

void unknown_undo_restore_685030()
{
    for (int index = unknown_UndoInfoStruct_list_00abce18.Count() - 1; index >= 0; index--) {
        UndoInfoStruct &info = unknown_UndoInfoStruct_list_00abce18[index];
        unknown_undo_cells_abceac[info.unknown_04 * unknown_undo_width_8286e4 + info.unknown_00].Value = info.unknown_08;
    }
    unknown_UndoInfoStruct_list_00abce18.Clear();
}
