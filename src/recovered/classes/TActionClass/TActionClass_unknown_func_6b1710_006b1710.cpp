// bool TActionClass::unknown_func_6b1710(...) (0x006B1710)
// Creates the animation of type index Data.Value at the waypoint +0x44 (ground height, bridge level counted), flagged +0x178; always true.
#include "shared/taction.hpp"
#include "shared/id_source.hpp"
#include "shared/map_view.hpp"
#include "shared/unknown_geometry.hpp"
#include "shared/anim.hpp"
#include "shared/anim_type.hpp"
// @ref ?Get_Waypoint_Location@UnknownIDSource@@QBE?AVCell@@H@Z=00663180

bool TActionClass::unknown_func_6b1710(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell)
{
    Cell waypoint = unknown_id_source_a3d290->Get_Waypoint_Location(unknown_44);
    CoordStruct coord = CoordStruct(waypoint);
    coord.Z = Map.Unknown_0055A280(coord);
    if ((Map[waypoint].unknown_140 & 0x100) || (Map[waypoint].unknown_140 & 0x400)) {
        coord.Z += unknown_geometry_j;
    }
    (new AnimClass(AnimTypes[Data.Value], coord, 0, 1, 0x600, 0))->unknown_178 = true;
    return true;
}


