// bool TActionClass::unknown_reveal_zone_of_waypoint(...) (0x006B0840)
// Unless the player's house flag +0x188 is set: Sight_From the player (radius 2, twice) at every cell of the local-map walk in the zone of waypoint Data (Red Alert's TACTION_REVEAL_ZONE); always true.
// bool TActionClass::unknown_reveal_zone_of_waypoint(...) (0x006B0840)
// Red Alert's TACTION_REVEAL_ZONE: unless the player sees the whole map (+0x188), every cell of the local map
// in the movement zone of waypoint Data is sighted twice for the player (radius 2, from the cell centre moved
// back by half its bridge height and raised to it); always true.
#include "shared/taction.hpp"
#include "shared/house.hpp"
#include "shared/map_cell.hpp"
#include "shared/map_view.hpp"
#include "shared/id_source.hpp"
#include "shared/unknown_geometry.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Get_Waypoint_Location@UnknownIDSource@@QBE?AVCell@@H@Z=00663180
// @ref ?Zone@MapClass@@QAEHABVCell@@H_N@Z=0054f8f0
// @ref ?Unknown_0055AA50@MapClass@@QAEXXZ=0055aa50
// @ref ?Unknown_0055A910@MapClass@@QAEPAVCellClass@@XZ=0055a910
// @ref ?Sight_From@MapClass@@QAEXABUCoordStruct@@HPAVHouseClass@@_N2H2H@Z=0054a110
// @ref _unknown_geometry_g=00abfe08


bool TActionClass::unknown_reveal_zone_of_waypoint(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell)
{
    if (!unknown_player_a35db4->unknown_188) {
        int zone = Map.Zone(unknown_id_source_a3d290->Get_Waypoint_Location(Data), 1, false);
        Map.Unknown_0055AA50();
        CellClass *cellptr;
        while ((cellptr = Map.Unknown_0055A910()) != 0) {
            Cell const &where = cellptr->MapCoords;
            if (Map.Zone(where, 1, false) == zone) {
                int level = cellptr->unknown_11b / 2;
                Cell spot = where - Cell(level / 2, level / 2);
                Map.Sight_From(XYZ_Coord(spot.X * 256 + 128, spot.Y * 256 + 128, unknown_geometry_g * level), 2, unknown_player_a35db4, false, false, 0, true, 0);
                spot = where - Cell(level / 2, level / 2);
                Map.Sight_From(XYZ_Coord(spot.X * 256 + 128, spot.Y * 256 + 128, unknown_geometry_g * level), 2, unknown_player_a35db4, false, false, 0, true, 1);
            }
        }
    }
    return true;
}
