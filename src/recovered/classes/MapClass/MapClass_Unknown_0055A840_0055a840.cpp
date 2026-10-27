// bool MapClass::Unknown_0055A840(Rect const &rect, Cell const &cell, bool flag) (0x0055A840)
// Whether a cell lies inside a rectangle in the map's diamond coordinates
// (0x0055A660 with the rectangle in place of the local map rectangle);
// with flag, the cell's height moves the X + Y bounds.
#include "shared/map.hpp"
#include "shared/map_cell.hpp"
#include "shared/map_view.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?unknown_dummy_cell_a6f9f8@@3VCellClass@@A=00a6f9f8

bool MapClass::Unknown_0055A840(Rect const &rect, Cell const &cell, bool flag)
{
    int height = 0;
    int x = cell.X;
    int y = cell.Y;
    if (flag) {
        CellClass &object = Map[cell];
        height = object.unknown_11b;
        if (object.unknown_11c && x + y < MapSize.Width + rect.Y * 2 + 4 + height) {
            height++;
        }
    }
    if (x + y > MapSize.Width + rect.Y * 2 + height &&
        x + y <= MapSize.Width + (rect.Height + rect.Y) * 2 + 2 + height &&
        x - y < (rect.Width + rect.X) * 2 - MapSize.Width &&
        y - x < MapSize.Width - rect.X * 2) {
        return true;
    }
    return false;
}
