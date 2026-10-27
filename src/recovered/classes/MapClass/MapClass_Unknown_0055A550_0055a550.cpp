// void MapClass::Unknown_0055A550() (0x0055A550)
// Starts the cell walk of 0x0055A490 at cell (1, width): a diagonal row of
// width - 1 more cells.
#include "shared/map.hpp"

void MapClass::Unknown_0055A550()
{
    unknown_108 = 1;
    unknown_10c = MapSize.Width;
    unknown_110 = MapSize.Width - 1;
    unknown_114 = &Cells[(MapSize.Width << 9) + 1];
}
