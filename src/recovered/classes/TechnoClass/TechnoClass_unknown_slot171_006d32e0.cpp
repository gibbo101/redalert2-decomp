// bool TechnoClass::unknown_slot171(CoordStruct const &coord) (0x006D32E0, slot 171)
// Whether the movement zone can reach the cell of a coordinate from the
// object's own cell (the map's path test 0x0054F7C0, with the target cell's
// bridge level); always for zone -1 or the zero coordinate.
#include "shared/techno.hpp"
#include "shared/gscreen.hpp"
#include "shared/techno_map.hpp"
#include "shared/unknown_geometry.hpp"
// @ref _unknown_geometry_l=00ac0188

bool TechnoClass::unknown_slot171(CoordStruct const &coord)
{
    int zone = unknown_slot32()->MovementZone;
    if (zone != -1) {
        if (!(coord == unknown_geometry_l)) {
            Cell cell = Coord_Cell(coord);
            Cell here = Coord_Cell(unknown_slot19(0));
            return Map.Unknown_0054F7C0(here, cell, zone, unknown_slot46(0),
                (unsigned char)((((UnknownCellClass *)&Map[cell])->Flags >> 8) & 1), unknown_slot189());
        }
    }
    return true;
}
