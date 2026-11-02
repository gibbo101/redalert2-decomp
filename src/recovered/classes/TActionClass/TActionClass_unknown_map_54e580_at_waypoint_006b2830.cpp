// bool TActionClass::unknown_map_54e580_at_waypoint(...) (0x006B2830)
// Calls Map.Unknown_0054E580 with the cell of waypoint +0x44 and Data.Value; returns its result.
#include "shared/taction.hpp"
#include "shared/id_source.hpp"
#include "shared/map_view.hpp"
// @ref ?Get_Waypoint_Location@UnknownIDSource@@QBE?AVCell@@H@Z=00663180
// @ref ?Unknown_0054E580@MapClass@@QAE_NVCell@@H@Z=0054e580
// @ref ?Map@@3VMouseClass@@A=008324e0


bool TActionClass::unknown_map_54e580_at_waypoint(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell)
{
    Cell waypoint = unknown_id_source_a3d290->Get_Waypoint_Location(unknown_44);
    return Map.Unknown_0054E580(waypoint, Data.Value);
}


