// void HouseClass::unknown_func_4f3bb0(SuperClass *super) (0x004F3BB0)
// While the house has an enemy (+0x54F0), picks a target cell (0x004F65A0
// for target mode 1, else 0x004F6A80 by mode) and fires the super weapon at it.
// @ref ?unknown_cell_a40f10@@3VCell@@A=00a40f10
// @ref ?unknown_func_4f65a0@HouseClass@@QAE?AVCell@@XZ=004f65a0
// @ref ?unknown_func_4f6a80@HouseClass@@QAE?AVCell@@H@Z=004f6a80
#include "shared/techno.hpp"

void HouseClass::unknown_func_4f3bb0(SuperClass *super)
{
    if (unknown_54f0 != -1) {
        Cell cell = unknown_cell_a40f10;
        if (unknown_541c == 1) {
            cell = unknown_func_4f65a0();
        } else {
            cell = unknown_func_4f6a80(unknown_541c);
        }
        if (cell != unknown_cell_a40f10) {
            unknown_func_4e68d0(Supers.ID(super), &cell);
        }
    }
}
