// bool TActionClass::unknown_look_at_waypoint(...) (0x006B1B00)
// Tells the tactical view to look at the waypoint +0x44 (its cell centre at ground height, raised on a bridge) with Data.Value; always true.
#include "shared/taction.hpp"
#include "shared/id_source.hpp"
#include "shared/map_view.hpp"
#include "shared/tactical.hpp"
#include "shared/unknown_geometry.hpp"
// @ref ?Get_Waypoint_Location@UnknownIDSource@@QBE?AVCell@@H@Z=00663180

bool TActionClass::unknown_look_at_waypoint(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell)
{
    Cell waypoint = unknown_id_source_a3d290->Get_Waypoint_Location(unknown_44);
    UnknownCoord434820 coord = UnknownCoord434820(waypoint);
    coord.Z = Map.Unknown_0055A280(coord);
    if ((Map[waypoint].unknown_140 & 0x100) || (Map[waypoint].unknown_140 & 0x400)) {
        coord.Z += unknown_geometry_j;
    }
    unknown_tactical_83996c->Setup_Trigger_Scroll(coord, Data.Value);
    return true;
}


