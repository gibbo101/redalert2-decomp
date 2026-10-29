// void HouseClass::unknown_func_4f3c50(SuperClass *super) (0x004F3C50)
// Fires a super weapon (0x004E68D0) at a cell: with target mode +0x541C 1, two
// cells beyond the reachable cell nearest the base centre of the house the
// computer is angry at (+0x54F0, else this house); otherwise at the mode's
// cell (0x004F6A80). Nothing happens when no cell is found.
#include "shared/techno.hpp"
#include "shared/map_view.hpp"
// @ref ?Unknown_005502E0@MapClass@@QAE?AVCell@@ABV2@HHH_NUPoint2D@@HHHH0H@Z=005502e0

void HouseClass::unknown_func_4f3c50(SuperClass *super)
{
    HouseClass *house = unknown_54f0 != -1 ? Houses[unknown_54f0] : this;
    Cell cell = unknown_cell_a40f10;
    if (unknown_541c != 1) {
        cell = unknown_func_4f6a80(unknown_541c);
    } else {
        cell = Coord_Cell(house->BaseCenter);
        cell = Map.Unknown_005502E0(cell, 0, -1, 0, false, Point2D(5, 5), 0, 0, 0, 1, Cell(0, 0), 0);
        cell.X += 2;
        cell.Y += 2;
    }
    if (cell != unknown_cell_a40f10) {
        unknown_func_4e68d0(Supers.ID(super), cell);
    }
}
