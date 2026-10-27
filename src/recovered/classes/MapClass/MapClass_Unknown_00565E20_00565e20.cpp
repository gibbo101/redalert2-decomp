// bool MapClass::Unknown_00565E20(Rect const &rect) (0x00565E20)
// Whether every cell of a cell rectangle (of the global Map) has +0x4C
// 3 or 4.
#include "shared/map.hpp"
#include "shared/map_cell.hpp"
#include "shared/map_view.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?unknown_dummy_cell_a6f9f8@@3VCellClass@@A=00a6f9f8

bool MapClass::Unknown_00565E20(Rect const &rect)
{
    int height = rect.Height;
    int width = rect.Width;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int kind = Map[XY_Cell(rect.X + x, rect.Y + y)].unknown_4c;
            if (kind != 4 && kind != 3) {
                return false;
            }
        }
    }
    return true;
}
