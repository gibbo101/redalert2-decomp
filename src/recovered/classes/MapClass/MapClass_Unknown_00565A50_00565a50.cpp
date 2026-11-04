// MapClass::Unknown_00565A50: collects clear cells on successive square rings around origin in one zone.
#include "shared/map.hpp"
#include "shared/map_view.hpp"
#include "shared/map_cell.hpp"
// @ref ?Add@?$DynamicVectorClass@VCell@@@@QAE_NABVCell@@@Z=0056ba30
// @ref ??0Rect@@QAE@HHHH@Z=0042bcd0

void MapClass::Unknown_00565A50(Cell const &origin, int radius_limit, int count_limit, int zone_type, int zone, DynamicVectorClass<Cell> &cells, int width, int height)
{
    for (int radius = 1; radius <= radius_limit; radius++) {
        int negative_radius = -radius;
        for (int offset = negative_radius; offset <= radius; ++offset) {
            Cell candidate = (Cell)(origin + Cell(radius, offset));
            if (Zone(candidate, zone_type, false) == zone) {
                if (Unknown_00565E20(Rect(candidate.X, candidate.Y, width, height)))
                    cells.Add(candidate);
            }
            candidate = (Cell)(origin + Cell(-radius, offset));
            if (Zone(candidate, zone_type, false) == zone) {
                if (Unknown_00565E20(Rect(candidate.X, candidate.Y, width, height)))
                    cells.Add(candidate);
            }
            if (offset != radius && offset != negative_radius) {
                candidate = (Cell)(origin + Cell(offset, radius));
                if (Zone(candidate, zone_type, false) == zone) {
                    if (Unknown_00565E20(Rect(candidate.X, candidate.Y, width, height)))
                        cells.Add(candidate);
                }
                candidate = (Cell)(origin + Cell(offset, negative_radius));
                if (Zone(candidate, zone_type, false) == zone) {
                    if (Unknown_00565E20(Rect(candidate.X, candidate.Y, width, height)))
                        cells.Add(candidate);
                }
            }
        }
        if (cells.Count() > count_limit) return;
    }
}
