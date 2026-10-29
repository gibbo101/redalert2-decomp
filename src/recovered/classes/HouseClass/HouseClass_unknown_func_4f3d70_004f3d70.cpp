// void HouseClass::unknown_func_4f3d70(SuperClass *super) (0x004F3D70)
// As 0x004F3AE0, unless 0x0051FC50's flag is set.
// @ref ?unknown_cell_a40f10@@3VCell@@A=00a40f10
// @ref ?unknown_func_4f65a0@HouseClass@@QAE?AVCell@@XZ=004f65a0
// @ref ?unknown_func_4f6a80@HouseClass@@QAE?AVCell@@H@Z=004f6a80
#include "shared/techno.hpp"
#include "shared/team.hpp"

void HouseClass::unknown_func_4f3d70(SuperClass *super)
{
    if (!Unknown_0051FC50() && unknown_54f0 != -1) {
        Cell cell = unknown_cell_a40f10;
        if (unknown_541c == 1) {
            cell = unknown_func_4f65a0();
        } else {
            cell = unknown_func_4f6a80(unknown_541c);
        }
        if (cell != unknown_cell_a40f10) {
            unknown_func_4e68d0(Supers.ID(super), cell);
        }
    }
}
