// bool TActionClass::unknown_reveal_6b1050(...) (0x006B1050)
// TibSun TAction_REVEAL_SOME shape: unless the player sees everything, Map 0x0054A720 reveals the rules
// RevealTriggerRadius around waypoint Data (raised by half the cell height, bridges +4), then 0x0055A300; always true.
#include "shared/taction.hpp"
#include "shared/house.hpp"
#include "shared/id_source.hpp"
#include "shared/map_cell.hpp"
#include "shared/map_view.hpp"
#include "shared/rules.hpp"
#include "shared/unknown_geometry.hpp"
// @ref ?Get_Waypoint_Location@UnknownIDSource@@QBE?AVCell@@H@Z=00663180
// @ref ?Unknown_0054A720@MapClass@@QAEXABUCoordStruct@@H@Z=0054a720
// @ref ?Unknown_0055A300@MapClass@@QAEXXZ=0055a300
// @ref _unknown_geometry_g=00abfe08


bool TActionClass::unknown_reveal_6b1050(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell)
{
    if (!unknown_player_a35db4->unknown_188) {
        Cell waypoint = unknown_id_source_a3d290->Get_Waypoint_Location(Data);
        int extra;
        if ((Map[waypoint].unknown_140 & 0x100) || (Map[waypoint].unknown_140 & 0x400)) {
            extra = 4;
        } else {
            extra = 0;
        }
        int size = Map[waypoint].unknown_11b + extra;
        Cell spot = waypoint - Cell(size / 2, size / 2);
        Map.Unknown_0054A720(Cell_Coord(spot) + CoordStruct(0, 0, unknown_geometry_g * size), Rules->RevealTriggerRadius);
        Map.Unknown_0055A300();
    }
    return true;
}
