// void DisplayClass::Unknown_00499970(Cell const &cell, bool set) (0x00499970)
// Sets (or clears) flag 4 of every cell of the list at +0x1188 placed at
// the given cell, for the cells on the map. The flag updates are written
// `x = x | 4`: the wordier body is above VC6's auto-inline size cap, so
// Set_Cursor_Shape (0x00499070) keeps both calls out of line as the original does.
#include "shared/display.hpp"
#include "shared/map_cell.hpp"
// @ref ?unknown_cell_852610@@3VCell@@A=00852610
// @ref ?Unknown_0054AAB0@MapClass@@QAE_NABVCell@@@Z=0054aab0
// @ref ??AMapClass@@QAEAAVCellClass@@ABVCell@@@Z=00548070

void DisplayClass::Unknown_00499970(Cell const &cell, bool set)
{
    if (cell.X == unknown_cell_852610.X && cell.Y == unknown_cell_852610.Y) {
        return;
    }
    Cell const *offset = unknown_1188;
    while (*offset != Cell(0x7FFF, 0x7FFF)) {
        Cell target = cell + *offset++;
        if (Unknown_0054AAB0(target)) {
            CellClass &target_cell = (*this)[target];
            if (set) {
                target_cell.unknown_12c = target_cell.unknown_12c | 4;
            } else {
                target_cell.unknown_12c = target_cell.unknown_12c & ~4;
            }
        }
    }
}
