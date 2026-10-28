// Rewrites [Waypoints] from the set waypoints (0x00663350).
// @ref ?unknown_waypoints_section_7a9218@@3PBDB=007a9218
#include "shared/id_source.hpp"
#include "shared/map_view.hpp"
#include "shared/cell.hpp"
#include "shared/ccini_class.hpp"
#include "shared/win32_api.hpp"
#include "shared/waypoint_string.hpp"
#include "shared/unknown_geometry.hpp"

void UnknownIDSource::Write_Waypoints(CCINIClass &ini)
{
    ini.Clear(unknown_waypoints_section_7a9218);
    for (int index = 0; index < 101; index++) {
        if (Waypoints[index] != unknown_geometry_k) {
            char buffer[32];
            wsprintfA(buffer, "%d", index);
            ini.Put_Int(unknown_waypoints_section_7a9218, buffer, Waypoints[index].X + Waypoints[index].Y * 1000);
        }
    }
}
