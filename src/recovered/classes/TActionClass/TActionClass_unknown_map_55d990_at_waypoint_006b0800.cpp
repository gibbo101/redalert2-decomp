// bool TActionClass::unknown_map_55d990_at_waypoint(...) (0x006B0800)
// Calls Map.Unknown_0055D990 with the cell of waypoint Data.Value; always true.
#include "shared/taction.hpp"
#include "shared/id_source.hpp"
#include "shared/map_view.hpp"
// @ref ?Get_Waypoint_Location@UnknownIDSource@@QBE?AVCell@@H@Z=00663180
// @ref ?Unknown_0055D990@MapClass@@QAEXABVCell@@@Z=0055d990
// @ref ?Map@@3VMouseClass@@A=008324e0


bool TActionClass::unknown_map_55d990_at_waypoint(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell)
{
    Cell waypoint = unknown_id_source_a3d290->Get_Waypoint_Location(Data.Value);
    Map.Unknown_0055D990(waypoint);
    return true;
}


