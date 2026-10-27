// bool MapClass::Unknown_0055A660(Cell const &cell, bool flag) (0x0055A660)
// Whether a cell lies inside the local map rectangle (+0xF8) in the map's
// diamond coordinates; with flag, the cell's height (+0x11B, one more on a
// bridge cell, +0x11C, below the top band) moves the X + Y bounds.
#include "shared/map.hpp"
#include "shared/map_cell.hpp"
#include "shared/map_view.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?unknown_dummy_cell_a6f9f8@@3VCellClass@@A=00a6f9f8

bool MapClass::Unknown_0055A660(Cell const &cell, bool flag)
{
    int height = 0;
    int x = cell.X;
    int y = cell.Y;
    if (flag) {
        CellClass &object = Map[cell];
        height = object.unknown_11b;
        if (object.unknown_11c && x + y < MapSize.Width + MapLocalSize.Y * 2 + 4 + height) {
            height++;
        }
    }
    if (x + y > MapSize.Width + MapLocalSize.Y * 2 + height &&
        x + y <= MapSize.Width + (MapLocalSize.Height + MapLocalSize.Y) * 2 + 2 + height &&
        x - y < (MapLocalSize.Width + MapLocalSize.X) * 2 - MapSize.Width &&
        y - x < MapSize.Width - MapLocalSize.X * 2) {
        return true;
    }
    return false;
}
