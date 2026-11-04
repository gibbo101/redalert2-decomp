// Cell MapClass::Unknown_00564F70(CellClass *cptr, bool isbridge) (0x00564F70)
// The zone connection cell of a cell (TibSun Get_Bridge_Zone_Connection_Cell): a cell
// under a bridge (+0x140 bit 8) with isbridge maps to the connection at it
// (0x005500D0, distance 2), or without one to the bridge end of 0x005653C0 when there is
// one; the cell is offset along the connection (+0x140 bit 11: east/west) from its From.
// On a passable connection the nearer end, else walking east or south off the bridge,
// To when the cell reached is a bridge tile whose land type is not 3, else From.
#include "shared/map.hpp"
#include "shared/map_view.hpp"
#include "shared/map_cell.hpp"
#include "shared/coord_distance.hpp"
// @ref ?Unknown_005653C0@MapClass@@QAE?AVCell@@ABV2@0@Z=005653c0

Cell MapClass::Unknown_00564F70(CellClass *cptr, bool isbridge)
{
    Cell ncell;

    if (isbridge && (cptr->unknown_140 & 0x100)) {
        int cidx = Map.Unknown_005500D0(cptr->MapCoords, 2, 0);
        if (cidx == -1) {
            ncell = Unknown_005653C0(cptr->MapCoords, cptr->MapCoords);
            if ((Cell)ncell != unknown_cell_a6f238) {
                return (Cell)ncell;
            }
        }

        ZoneConnectionClass *zcon = &Map.ZoneConnections[cidx];
        if (cptr->unknown_140 & 0x800) {
            ncell = Cell(0, cptr->MapCoords.Y - zcon->From.Y);
        } else {
            ncell = Cell(cptr->MapCoords.X - zcon->From.X, 0);
        }

        if (zcon->unknown_08) {
            Cell d1 = zcon->From + ncell - cptr->MapCoords;
            short dist1 = Cell_Distance(d1.X, d1.Y);
            Cell d2 = zcon->To + ncell - cptr->MapCoords;
            short dist2 = Cell_Distance(d2.X, d2.Y);
            if (dist1 < dist2) {
                return zcon->From + ncell;
            } else {
                return zcon->To + ncell;
            }
        } else {
            int facing = zcon->From.X != zcon->To.X ? 2 : 4;
            while (cptr->unknown_140 & 0x100) {
                cptr = &cptr->Adjacent_Cell(facing);
            }
            if ((cptr->unknown_47b960() || cptr->unknown_47b980()) && cptr->unknown_ec != 3) {
                return zcon->To + ncell;
            } else {
                return zcon->From + ncell;
            }
        }
    }

    return cptr->MapCoords;
}
