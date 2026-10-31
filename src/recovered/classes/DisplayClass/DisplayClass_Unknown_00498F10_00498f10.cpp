// void DisplayClass::Unknown_00498F10(Cell const *list) (0x00498F10)
// Set_Cursor_Shape's twin for the cursor list at +0x1178 (cell +0x1170 plus offset +0x1174, cell
// flag 2 through 0x004998C0): unmarks the old list, copies the new 0x7FFF-terminated list into a
// function static (0x00852634, 120 cells, guard 0x00852838; its empty atexit thunk is 0x00499060)
// and centres it on the cell.
#include "shared/display.hpp"
#include "shared/crt_memory.hpp"
// @ref ?unknown_cell_852610@@3VCell@@A=00852610
// @ref _?_list@?7??Unknown_00498F10@DisplayClass@@QAEXPBVCell@@@Z@4PAV3@A=00852634
// @ref _?$S69@?7??Unknown_00498F10@DisplayClass@@QAEXPBVCell@@@Z@4EA=00852838

void DisplayClass::Unknown_00498F10(Cell const *list)
{
    if (unknown_1178) {
        Unknown_004998C0(unknown_1174 + unknown_1170, false);
    }
    unknown_1174 = unknown_cell_852610;

    if (list) {
        static Cell _list[120];

        memcpy(_list, list, sizeof(_list));
        unknown_1178 = _list;
        Cell size = Unknown_00499810(unknown_1178);
        size.X--;
        size.Y--;
        size = Cell(-size.X, -size.Y);
        unknown_1174 = Cell(size.X / 2, size.Y / 2);
        Unknown_004998C0(unknown_1174 + unknown_1170, true);
    } else {
        unknown_1178 = 0;
    }
}
