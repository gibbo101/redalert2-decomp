// void TeamClass::TMission_unknown_6bc7b0(ScriptMissionClass const &mission, int unknown) (0x006BC7B0)
// Picks a target of a building type (Data: type index in the low word, a value in the high word) for
// the first member and targets the reachable cell nearest it in the first member's movement zone
// (none when there is none); completes the step when the team has no second target, then runs 0x006BA1A0.
#include "shared/unit.hpp"
#include "shared/foot.hpp"
#include "shared/team.hpp"
#include "shared/team_type.hpp"
#include "shared/techno_type.hpp"
#include "shared/house.hpp"
#include "shared/map_view.hpp"
#include "shared/cell.hpp"
// @ref ?Unknown_006BCF70@@YIPAVAbstractClass@@PAVBuildingTypeClass@@PAVHouseClass@@PAVFootClass@@H_N@Z=006bcf70
// @ref ?unknown_func_6b79e0@TeamClass@@QAEXPAVAbstractClass@@@Z=006b79e0
// @ref ?unknown_func_6ba1a0@TeamClass@@QAEXXZ=006ba1a0
// @ref ?BuildingTypes@@3V?$DynamicVectorClass@PAVBuildingTypeClass@@@@A=00a35cd8
// @ref ?Houses@@3V?$DynamicVectorClass@PAVHouseClass@@@@A=00a32298
// @ref _unknown_geometry_k=00ac0050

extern DynamicVectorClass<BuildingTypeClass *> BuildingTypes;      // 0x00A35CD8

void TeamClass::TMission_unknown_6bc7b0(ScriptMissionClass const &mission, int unknown)
{
    if (unknown_3c == 0 && Member != 0) {
        FootClass *first = Member;
        int value = (mission.Data >> 16) & 0xFFFF;
        BuildingTypeClass *type = BuildingTypes[mission.Data & 0xFFFF];
        HouseClass *enemy = 0;
        if (first->House->unknown_54f0 != -1) {
            enemy = Houses[first->House->unknown_54f0];
        }
        AbstractClass *target = Unknown_006BCF70(type, enemy, first, value, Class->OnlyTargetHouseEnemy);
        if (target != 0) {
            int zone_type = first->unknown_slot32()->MovementZone;
            CoordStruct coord = ((ObjectClass *)target)->Coord;
            Cell cell = Coord_Cell(coord);
            Cell found = Map.Unknown_005502E0(cell, first->unknown_slot32()->SpeedType,
                Map.Zone(Coord_Cell(first->Center_Coord()), zone_type, first->unknown_79), zone_type, false,
                Point2D(1, 1), 0, 0, 0, 1, Cell(0, 0), 0);
            if (found != unknown_geometry_k) {
                unknown_func_6b79e0(&Map[found]);
            } else {
                unknown_func_6b79e0(0);
            }
        }
        if (unknown_3c == 0) {
            StepCompleted = true;
        }
    }
    unknown_func_6ba1a0();
}
