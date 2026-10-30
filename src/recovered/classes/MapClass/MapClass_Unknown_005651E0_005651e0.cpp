// Cell MapClass::Unknown_005651E0(Cell const &cell, Cell const &from) (0x005651E0)
// For a cell on a zone connection (0x005500D0, distance 1): with +0x08 set,
// the connection end nearer to from; otherwise walks from the cell along the
// connection (east when the ends' X differ, else south) while the cell's
// +0x140 bit 8 is set and returns To when the cell reached is a bridge tile
// (0x0047B960 / 0x0047B980) whose land type is not 3, else From. Off any
// connection, the cell from 0x005653C0 unless it is invalid, else the cell.
#include "shared/map.hpp"
#include "shared/map_view.hpp"
#include "shared/map_cell.hpp"
#include "shared/coord_distance.hpp"
// @ref ?Unknown_005653C0@MapClass@@QAE?AVCell@@ABV2@0@Z=005653c0

Cell MapClass::Unknown_005651E0(Cell const &cell, Cell const &from)
{
    int index = Map.Unknown_005500D0(cell, 1, 0);
    if (index != -1) {
        ZoneConnectionClass &connection = Map.ZoneConnections[index];
        if (connection.unknown_08) {
            Cell d1 = from - connection.From;
            short dist1 = unknown_sqrt_4ba410((double)d1.X * d1.X + (double)d1.Y * d1.Y);
            Cell d2 = from - connection.To;
            short dist2 = unknown_sqrt_4ba410((double)d2.X * d2.X + (double)d2.Y * d2.Y);
            if (dist1 < dist2) {
                return connection.From;
            }
            return connection.To;
        }
        int facing = (short)(connection.From.X - connection.To.X) ? 2 : 4;
        CellClass *cellptr = &Map[cell];
        while (cellptr->unknown_140 & 0x100) {
            cellptr = &cellptr->Adjacent_Cell(facing);
        }
        if ((cellptr->unknown_47b960() || cellptr->unknown_47b980()) && cellptr->unknown_ec != 3) {
            return connection.To;
        }
        return connection.From;
    }
    Cell result = Unknown_005653C0(cell, from);
    if (result != unknown_cell_a6f238) {
        return result;
    }
    return cell;
}
