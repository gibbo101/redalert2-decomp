// WaypointPathClass::WaypointPathClass() (0x00724B10): an empty path with no
// selected waypoint, added to the unit's path list.
#include "shared/waypoint_path.hpp"

WaypointPathClass::WaypointPathClass() :
    Selected(-1)
{
    unknown_WaypointPathClass_list_00b25590.Add(this);
}
