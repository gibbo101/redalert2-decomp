// bool HouseClass::unknown_4e76a0(Cell const &cell, bool arg2) (0x004E76A0)
// Keeps the cell as the house's held object (+0x5308): releases the old one
// (0x004E7580), then marks the cell, or the nearest cell that takes the
// house, and stores that cell; false when none does.
#include "shared/techno.hpp"
#include "shared/unknown_geometry.hpp"
#include "shared/map_view.hpp"
#include "shared/cell.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?unknown_cell_a40f10@@3VCell@@A=00a40f10

bool HouseClass::unknown_4e76a0(Cell const &cell, bool arg2)
{
    if (Map.Unknown_0054AAB0(cell)) {
        unknown_func_4e7580(unknown_5308, arg2);
        Cell target = cell;
        bool ok = Map[target].unknown_4786d0(Type->House);
        if (!ok) {
            target = Map.Unknown_005502E0(cell, 1, -1, 0, false, Point2D(1, 1), 0, 0, 0, 1, Cell(0, 0), 0);
            if (target != unknown_cell_a40f10) {
                ok = Map[target].unknown_4786d0(Type->House);
            }
        }
        if (ok) {
            unknown_5308 = &Map[target];
        }
        return ok;
    }
    return false;
}
