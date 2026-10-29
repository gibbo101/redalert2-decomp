// bool TActionClass::unknown_center_on_waypoint(...) (0x006B1BC0)
// Moves the tactical view to waypoint +0x44 (its cell centre at ground height, raised on a bridge); always true.
#include "shared/taction.hpp"
#include "shared/id_source.hpp"
#include "shared/map_cell.hpp"
#include "shared/map_view.hpp"
#include "shared/tactical.hpp"
#include "shared/unknown_geometry.hpp"
// @ref ?Unknown_006A66B0@Tactical@@QAEXABUCoordStruct@@@Z=006a66b0
// @ref _unknown_geometry_j=00abfdf8
// @ref ?Get_Waypoint_Location@UnknownIDSource@@QBE?AVCell@@H@Z=00663180

bool TActionClass::unknown_center_on_waypoint(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell)
{
    Cell waypoint = unknown_id_source_a3d290->Get_Waypoint_Location(unknown_44);
    CoordStruct coord = Cell_Center(waypoint);
    coord.Z = Map.Unknown_0055A280(coord);
    if ((Map[waypoint].unknown_140 & 0x100) || (Map[waypoint].unknown_140 & 0x400)) {
        coord.Z += unknown_geometry_j;
    }
    unknown_tactical_83996c->Unknown_006A66B0(coord);
    return true;
}
