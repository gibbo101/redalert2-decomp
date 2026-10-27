// bool AITriggerTypeClass::Team_Zone_Check(TeamTypeClass *team, HouseClass *house, HouseClass *enemy) const (0x0041E130)
// For a team that cares (unknown_e8): whether the house's and the enemy's base
// centres lie in the same movement zone of the team's zone type
// (unknown_e4); when the team allows it (unknown_e9), zones that differ for
// its type but match for zone type 5 also pass. True otherwise.
#include "shared/ai_trigger_type.hpp"
#include "shared/house.hpp"
#include "shared/map_view.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Zone@MapClass@@QAEHABVCell@@H_N@Z=0054f8f0

bool AITriggerTypeClass::Team_Zone_Check(TeamTypeClass *team, HouseClass *house, HouseClass *enemy) const
{
    if (!team->unknown_e8 || enemy == 0) {
        return true;
    }
    Cell house_cell = Coord_Cell(house->BaseCenter);
    int zone_type = team->unknown_e4;
    Cell enemy_cell = Coord_Cell(enemy->BaseCenter);
    if (team->unknown_e9) {
        int enemy_zone = Map.Zone(enemy_cell, zone_type, false);
        if (Map.Zone(house_cell, zone_type, false) != enemy_zone) {
            enemy_zone = Map.Zone(enemy_cell, 5, false);
            if (Map.Zone(house_cell, 5, false) == enemy_zone) {
                return true;
            }
        }
        return false;
    }
    int enemy_zone = Map.Zone(enemy_cell, zone_type, false);
    bool same = Map.Zone(house_cell, zone_type, false) == enemy_zone;
    return same;
}
