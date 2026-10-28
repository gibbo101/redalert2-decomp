// The centre of a waypoint's cell, raised by the bridge height on a bridge
// cell (0x006631C0).
#include "shared/id_source.hpp"
#include "shared/map_view.hpp"
#include "shared/cell.hpp"
#include "shared/ccini_class.hpp"
#include "shared/win32_api.hpp"
#include "shared/waypoint_string.hpp"
#include "shared/unknown_geometry.hpp"

CoordStruct UnknownIDSource::Waypoint_Coord(int waypoint) const
{
    CellClass &cell = Map[Waypoints[waypoint]];
    CoordStruct coord = cell.Center_Coord();
    if (cell.unknown_140 & 0x500) {
        coord.Z += unknown_geometry_j;
    }
    return coord;
}
