// bool TActionClass::unknown_func_6b1270(...) (0x006B1270)
// Creates the animation of the rules DropZoneAnim type at the waypoint +0x44 (ground height, bridge level counted), flagged +0x178; always true.
#include "shared/taction.hpp"
#include "shared/id_source.hpp"
#include "shared/map_view.hpp"
#include "shared/unknown_geometry.hpp"
#include "shared/anim.hpp"
#include "shared/anim_type.hpp"
#include "shared/rules.hpp"
// @ref ?Get_Waypoint_Location@UnknownIDSource@@QBE?AVCell@@H@Z=00663180

bool TActionClass::unknown_func_6b1270(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell)
{
    Cell waypoint = unknown_id_source_a3d290->Get_Waypoint_Location(unknown_44);
    CoordStruct coord = CoordStruct(waypoint);
    coord.Z = Map.Unknown_0055A280(coord);
    unsigned int bridge_flags = Map[waypoint].unknown_140;
    if ((bridge_flags & 0x100) || (Map[waypoint].unknown_140 & 0x400)) {
        int bridge_height = unknown_geometry_j;
        coord.Z += bridge_height;
    }
    (new AnimClass(Rules->DropZoneAnim, coord, 0, 1, 0x600, 0))->unknown_178 = true;
    return true;
}


