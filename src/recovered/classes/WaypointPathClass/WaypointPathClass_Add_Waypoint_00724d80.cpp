// bool WaypointPathClass::Add_Waypoint(CoordStruct const &coord) (0x00724D80):
// adds the centre of coord's cell (at coord's height) unless a waypoint is
// selected; always answers true.
#include "shared/waypoint_path.hpp"
#include "shared/cell.hpp"
#include "shared/object.hpp"

bool WaypointPathClass::Add_Waypoint(CoordStruct const &coord)
{
    WaypointClass waypoint;
    waypoint.Coord = Cell_Center(Coord_Cell(coord));
    waypoint.Coord.Z = coord.Z;
    if (Selected != -1) {
        return true;
    }
    Waypoints.Add(waypoint);
    return true;
}
