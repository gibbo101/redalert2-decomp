// int MapClass::Zone(Cell const &cell, int zone_type, bool alt) (0x0054F8F0)
// The cell's zone for a zone type (TibSun Get_Cell_Zone): with alt, a cell under a
// bridge takes the zone of its connection's start, or of its end when the walk
// along the bridge (south or east) ends on a bridge tile that is not rock; -1
// without a connection (0x005500D0).
#include "shared/map.hpp"
#include "shared/map_cell.hpp"
// @ref ?unknown_47b960@CellClass@@QBE_NXZ=0047b960
// @ref ?unknown_47b980@CellClass@@QBE_NXZ=0047b980

int MapClass::Zone(Cell const &cell, int zone_type, bool alt)
{
    Cell const *p;
    if (alt && (Map[cell].unknown_140 & 0x100)) {
        int index = Unknown_005500D0(cell, 1, 0);
        if (index != -1) {
            ZoneConnectionClass &connection = ZoneConnections[index];
            if (connection.unknown_08) {
                p = &connection.From;
            } else {
                CellClass *cptr = &Map[cell];
                int facing = connection.From.X == connection.To.X ? 4 : 2;
                while (cptr->unknown_140 & 0x100) {
                    cptr = &cptr->Adjacent_Cell(facing);
                }
                if ((cptr->unknown_47b960() || cptr->unknown_47b980()) && cptr->unknown_ec != 3) {
                    p = &connection.To;
                } else {
                    p = &connection.From;
                }
            }
        } else {
            return -1;
        }
    } else {
        p = &cell;
    }
    return ((unsigned short *)unknown_18[zone_type])[Unknown_0054FA60(*p)];
}
