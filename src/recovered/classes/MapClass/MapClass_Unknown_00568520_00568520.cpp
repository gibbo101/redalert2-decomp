// void MapClass::Unknown_00568520(CellClass *cell, HouseClass *house, bool arg3) (0x00568520)
// Reveals the technos standing on the cells a shroud change uncovers (TibSun
// Reveal_Nearby_Technos): along the diagonal from the cell, the cell of each
// height band (heights i - 2 to i for i = 1, 3, ... 13) is marked for a radar
// redraw when arg3 is set, and its techno (CellClass 0x00471660) gets slot 96.
#include "shared/map.hpp"
#include "shared/map_view.hpp"
#include "shared/map_cell.hpp"
#include "shared/map_techno.hpp"
// @ref ?Unknown_006328F0@RadarClass@@QAEXABVCell@@@Z=006328f0

void MapClass::Unknown_00568520(CellClass *cell, HouseClass *house, bool arg3)
{
    Cell where = cell->MapCoords;
    for (int level = 1; level < 15; level += 2) {
        CellClass *cellptr = &Map[where];
        int height = cellptr->unknown_11b;
        if (height >= level - 2 && height <= level) {
            if (arg3) {
                Map.Unknown_006328F0(cellptr->MapCoords);
            }
            TechnoClass *techno = (TechnoClass *)cellptr->Unknown_00471660(Point2D(0, 0), 0, 0);
            if (techno != 0) {
                techno->unknown_slot96(house);
            }
        }
        where.X++;
        where.Y++;
    }
}
