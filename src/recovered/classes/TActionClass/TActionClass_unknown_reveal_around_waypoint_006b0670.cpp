// bool TActionClass::unknown_reveal_around_waypoint(...) (0x006B0670)
// Unless the player's house flag +0x188 is set: Sight_From the player twice (last argument 0, then 1) around waypoint Data, moved back by half its cell's +0x11B level (plus 4 on a bridge), raised by that level, with the rules RevealTriggerRadius (Red Alert's TACTION_REVEAL_SOME); always true.
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

// @ref ?Sight_From@MapClass@@QAEXABUCoordStruct@@HPAVHouseClass@@_N2H2H@Z=0054a110

bool TActionClass::unknown_reveal_around_waypoint(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell)
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
        Map.Sight_From(XYZ_Coord(spot.X * 256 + 128, spot.Y * 256 + 128, unknown_geometry_g * size), Rules->RevealTriggerRadius, unknown_player_a35db4, false, false, 0, true, 0);
        spot = waypoint - Cell(size / 2, size / 2);
        Map.Sight_From(XYZ_Coord(spot.X * 256 + 128, spot.Y * 256 + 128, unknown_geometry_g * size), Rules->RevealTriggerRadius, unknown_player_a35db4, false, false, 0, true, 1);
    }
    return true;
}
