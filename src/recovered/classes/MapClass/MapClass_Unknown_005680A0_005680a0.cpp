// bool MapClass::Unknown_005680A0(Cell const &cell, int radius) (0x005680A0)
// Whether any cell of the square of the given radius around a cell (of the
// global Map) has an occupier (+0xE4).
#include "shared/map.hpp"
#include "shared/map_cell.hpp"
#include "shared/map_view.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?unknown_dummy_cell_a6f9f8@@3VCellClass@@A=00a6f9f8

bool MapClass::Unknown_005680A0(Cell const &cell, int radius)
{
    for (int y = cell.Y - radius; y <= cell.Y + radius; y++) {
        for (int x = cell.X - radius; x <= cell.X + radius; x++) {
            if (Map[Cell(x, y)].OccupierPtr != 0) {
                return true;
            }
        }
    }
    return false;
}
