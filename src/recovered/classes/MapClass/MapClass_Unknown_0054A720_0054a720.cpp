// void MapClass::Unknown_0054A720(CoordStruct const &coord, int radius) (0x0054A720)
// Moves coord up the screen by its height (0x006A2970, in cells of 30
// pixels), then for every cell strictly inside radius + 1 of its cell whose
// +0x130 is clear sets +0x130 and clears +0x12C bits 3 and 4 (Map's cells;
// the reverse of 0x0054A8F0).
#include "shared/map.hpp"
#include "shared/map_view.hpp"
#include "shared/map_cell.hpp"
#include "shared/map_adjacent.hpp"

void MapClass::Unknown_0054A720(CoordStruct const &coord, int radius)
{
    CoordStruct center = coord;
    center.X += (Unknown_006A2970(center.Z) / -30) * 256;
    center.Y += (Unknown_006A2970(center.Z) / -30) * 256;
    Cell cell = Coord_Cell(center);

    for (int x = -2 - radius; x < radius + 2; x++) {
        for (int y = -2 - radius; y < radius + 2; y++) {
            if (x * x + y * y < (radius + 1) * (radius + 1)) {
                Cell newcell = XY_Cell(cell.X + x, cell.Y + y);
                if (Map[newcell].unknown_130 == 0) {
                    Map[newcell].unknown_130 = 1;
                    Map[newcell].unknown_12c &= ~8;
                    Map[newcell].unknown_12c &= ~0x10;
                }
            }
        }
    }
}
