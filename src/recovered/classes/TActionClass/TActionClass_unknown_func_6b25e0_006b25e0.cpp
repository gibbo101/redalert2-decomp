// bool TActionClass::unknown_func_6b25e0(...) (0x006B25E0)
// Starts the lightning storm (0x0051F930) over the cell of waypoint +0x44 (bridge level counted) with the rules'
// LightningStormDuration and LightningDeferment for house, unless Unknown_0051FC50 holds (then false); true otherwise.
#include "shared/taction.hpp"
#include "shared/id_source.hpp"
#include "shared/map_view.hpp"
#include "shared/object.hpp"
#include "shared/team.hpp"
#include "shared/rules.hpp"
#include "shared/unknown_geometry.hpp"
// @ref ?Get_Waypoint_Location@UnknownIDSource@@QBE?AVCell@@H@Z=00663180
// @ref ?Unknown_0051FC50@@YA_NXZ=0051fc50
// @ref ?Unknown_0051F930@@YIXHHVCell@@H@Z=0051f930

bool TActionClass::unknown_func_6b25e0(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell)
{
    Cell waypoint = unknown_id_source_a3d290->Get_Waypoint_Location(unknown_44);
    CoordStruct coord = CoordStruct(waypoint);
    coord.Z = Map.Unknown_0055A280(coord);
    if (Map[waypoint].unknown_140 & 0x100) {
        coord.Z += unknown_geometry_j;
    }
    Cell target = coord.As_Cell();
    if (!Unknown_0051FC50()) {
        Unknown_0051F930(Rules->LightningStormDuration, Rules->unknown_13e8, target, (int)house);
        return true;
    }
    return false;
}


