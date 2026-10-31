// void DisplayClass::Set_Cursor_Shape(Cell const *list) (0x00499070)
// Red Alert's DisplayClass::Set_Cursor_Shape: unmarks the old placement
// cursor (+0x1188 list at zone cell +0x117E plus offset +0x1182), copies the
// new 0x7FFF-terminated list into a function static (0x008524B0, guard
// 0x008525F0; its empty atexit thunk is 0x004991C0) and centres it on the
// zone cell.
// The size less (1, 1) is negated and halved with TPoint2D<short>'s operators.
#include "shared/display.hpp"
#include "shared/crt_memory.hpp"
// @ref ?unknown_cell_852610@@3VCell@@A=00852610
// @ref _?_list@?7??Set_Cursor_Shape@DisplayClass@@QAEXPBVCell@@@Z@4PAV3@A=008524b0
// @ref _?$S71@?7??Set_Cursor_Shape@DisplayClass@@QAEXPBVCell@@@Z@4EA=008525f0

void DisplayClass::Set_Cursor_Shape(Cell const *list)
{
    if (unknown_1188) {
        Unknown_00499970(unknown_117e + unknown_1182, false);
    }
    unknown_1182 = unknown_cell_852610;

    if (list) {
        static Cell _list[50];

        memcpy(_list, list, sizeof(_list));
        unknown_1188 = _list;
        Cell size = Unknown_00499810(unknown_1188);
        size -= Cell(1, 1);
        unknown_1182 = -size / 2;
        Unknown_00499970(unknown_117e + unknown_1182, true);
    } else {
        unknown_1188 = 0;
    }
}
