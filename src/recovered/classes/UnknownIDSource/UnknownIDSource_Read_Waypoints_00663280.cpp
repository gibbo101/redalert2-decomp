// Reads [Waypoints] ("index=x+y*1000"; missing entries are the empty cell)
// and marks the cells of the set waypoints (0x00663280).
// @ref ??_C@_09DFBC@Waypoints?$AA@=007e33dc
#include "shared/id_source.hpp"
#include "shared/map_view.hpp"
#include "shared/cell.hpp"
#include "shared/ccini_class.hpp"
#include "shared/win32_api.hpp"
#include "shared/waypoint_string.hpp"
#include "shared/unknown_geometry.hpp"

void UnknownIDSource::Read_Waypoints(CCINIClass &ini)
{
    for (int index = 0; index < 101; index++) {
        char buffer[20];
        wsprintfA(buffer, "%d", index);
        int value = ini.Get_Int("Waypoints", buffer, 0);
        if (value == 0) {
            Waypoints[index] = unknown_geometry_k;
        } else {
            Waypoints[index] = Cell(value % 1000, value / 1000);
        }
        if (Unknown_00663240(index)) {
            Map[Waypoints[index]].unknown_140 |= 4;
        }
    }
}
