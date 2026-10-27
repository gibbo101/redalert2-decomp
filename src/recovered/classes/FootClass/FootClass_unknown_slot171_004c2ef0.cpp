// bool FootClass::unknown_slot171(CoordStruct const &coord) (0x004C2EF0)
// Whether the unit's movement zone can reach the cell of a coordinate from
// its own cell (the map's path test 0x0054F7C0, with the target cell's
// bridge level); always for zone -1, never for the zero cell.
#include "shared/foot.hpp"
#include "shared/house.hpp"
#include "shared/techno_type.hpp"
#include "shared/map_view.hpp"

bool FootClass::unknown_slot171(CoordStruct const &coord)
{
    int zone = unknown_slot32()->MovementZone;
    if (zone == -1) {
        return true;
    }
    Cell cell = Coord_Cell(coord);
    if (cell == unknown_geometry_k) {
        return false;
    }
    Cell here = Coord_Cell(unknown_slot19(0));
    return Map.Unknown_0054F7C0(here, cell, zone, unknown_slot46(0),
        (unsigned char)((((UnknownCellClass *)&Map[cell])->Flags >> 8) & 1), unknown_slot189());
}
