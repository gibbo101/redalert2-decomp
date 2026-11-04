// CellClass *MapClass::Unknown_005629D0(AbstractClass *object) (0x005629D0)
// TibSun Find_Nearby_Shroud: up to 24 shrouded cells (0x00568140 at the ground height) that
// pass 0x0055A660 are gathered from square rings around the object's cell, out to the map's
// width plus height but at most 32 rings; one of them at random, else the object's own cell.
#include "shared/map.hpp"
#include "shared/map_view.hpp"
#include "shared/map_cell.hpp"
#include "shared/map_techno.hpp"
#include "shared/map_adjacent.hpp"
#include "shared/id_source.hpp"

CellClass *MapClass::Unknown_005629D0(AbstractClass *object)
{
    Cell cells[24];

    Cell center = Coord_Cell(object->Center_Coord());
    int found = 0;
    int xx = center.X;
    int yy = center.Y;

    int radius = 32;
    if (MapSize.Width + MapSize.Height <= 32) {
        radius = MapSize.Width + MapSize.Height;
    }

    for (int ring = 0; ring < radius; ring++) {

        for (int x = -ring; x <= ring; x++) {

            Cell cell = Cell(xx + x, yy - ring);
            if (Unknown_0055A660(cell, true)) {
                CoordStruct coord = Cell_Coord(cell);
                coord.Z = Unknown_0055A280(coord);
                if (Unknown_00568140(coord)) {
                    cells[found++] = cell;
                }
            }
            if (found == 24) {
                break;
            }

            cell = Cell(xx + x, yy + ring);
            if (Unknown_0055A660(cell, true)) {
                CoordStruct coord = Cell_Coord(cell);
                coord.Z = Unknown_0055A280(coord);
                if (Unknown_00568140(coord)) {
                    cells[found++] = cell;
                }
            }
            if (found == 24) {
                break;
            }
        }
        if (found == 24) {
            break;
        }

        for (int y = -ring + 1; y <= ring - 1; y++) {

            Cell cell = Cell(xx - ring, yy + y);
            if (Unknown_0055A660(cell, true)) {
                CoordStruct coord = Cell_Coord(cell);
                coord.Z = Unknown_0055A280(coord);
                if (Unknown_00568140(coord)) {
                    cells[found++] = cell;
                }
            }
            if (found == 24) {
                break;
            }

            cell = Cell(xx + ring, yy + y);
            if (Unknown_0055A660(cell, true)) {
                CoordStruct coord = Cell_Coord(cell);
                coord.Z = Unknown_0055A280(coord);
                if (Unknown_00568140(coord)) {
                    cells[found++] = cell;
                }
            }
            if (found == 24) {
                break;
            }
        }
        if (found == 24) {
            break;
        }
    }

    if (found > 0) {
        return &Map[cells[Random_Pick(0, found - 1)]];
    }

    return &Map[center];
}
