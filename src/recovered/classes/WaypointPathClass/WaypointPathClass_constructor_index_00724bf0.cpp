// WaypointPathClass::WaypointPathClass(int index) (0x00724BF0): an empty path
// that joins the unit's path list only for path numbers 0..11.
#include "shared/waypoint_path.hpp"

WaypointPathClass::WaypointPathClass(int index) :
    Selected(-1)
{
    if (index >= 0 && index < 12) {
        unknown_WaypointPathClass_list_00b25590.Add(this);
    }
}
