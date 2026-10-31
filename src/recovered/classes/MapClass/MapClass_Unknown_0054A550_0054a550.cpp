// void MapClass::Unknown_0054A550(CoordStruct const &coord, int start, int sightrange, int skip) (0x0054A550)
// Refreshes the shroud frame of the cells of the sight rings start..sightrange
// (sight 3-11, start 0-8) around coord moved up the screen by its height
// (the radius tables of 0x00549C50): each cell whose tactical shroud frame
// (0x006A8D40) changed takes it and is redrawn (0x006AADD0). Nothing when skip.
#include "shared/map.hpp"
#include "shared/map_view.hpp"
#include "shared/map_cell.hpp"
#include "shared/map_adjacent.hpp"
// @ref ?unknown_radius_count_7a5908@@3QBHB=007a5908
// @ref ?unknown_radius_offset_a6f248@@3QBVCell@@B=00a6f248

extern int const unknown_radius_count_7a5908[];
extern Cell const unknown_radius_offset_a6f248[];

void MapClass::Unknown_0054A550(CoordStruct const &coord, int start, int sightrange, int skip)
{
    if (sightrange > 11) {
        sightrange = 11;
    } else if (sightrange < 3) {
        sightrange = 3;
    }
    if (start < 0) {
        start = 0;
    } else if (start > 8) {
        start = 8;
    }
    int count = (start == 0) ? unknown_radius_count_7a5908[sightrange] : unknown_radius_count_7a5908[sightrange] - unknown_radius_count_7a5908[start - 1];

    if (!skip) {
        CoordStruct center = coord;
        center.X += (Unknown_006A2970(center.Z) / -30) * 256;
        center.Y += (Unknown_006A2970(center.Z) / -30) * 256;
        Cell cell = Coord_Cell(center);

        Cell const *ptr = &unknown_radius_offset_a6f248[0];
        if (start) {
            ptr += unknown_radius_count_7a5908[start - 1];
        }
        while (count--) {
            Cell newcell = *ptr++ + cell;
            CellClass &cellptr = (*this)[newcell];
            unsigned char frame = unknown_tactical_83996c->Cell_Shadow(newcell, 0);
            if (frame != cellptr.unknown_120) {
                cellptr.unknown_120 = frame;
                cellptr.unknown_138 = true;
                unknown_tactical_83996c->Unknown_006AADD0(&cellptr);
            }
        }
    }
}
