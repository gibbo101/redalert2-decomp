// void TeamClass::TMission_unknown_6be1c0(ScriptMissionClass const &mission, int unknown) (0x006BE1C0)
// Chronoshift: with the leader house's super weapons of types 3 and 4 (hypothesis: ChronoSphere and
// ChronoWarp) and the first ready, picks a building of type Data & 0xFFFF (mode Data >> 16, as 0x006BCF70)
// and fires both, 3 at the team's cell (+0x34) and 4 at the building's, which becomes the team's target;
// completes the step unless the first is still charging below the rules' AI ready fraction.
#include "shared/unit.hpp"
#include "shared/foot.hpp"
#include "shared/team.hpp"
#include "shared/team_type.hpp"
#include "shared/house.hpp"
#include "shared/super.hpp"
#include "shared/rules.hpp"
// @ref ?unknown_func_4e68d0@HouseClass@@QAE_NHABVCell@@@Z=004e68d0
// @ref ?Unknown_006BCF70@@YIPAVAbstractClass@@PAVBuildingTypeClass@@PAVHouseClass@@PAVFootClass@@H_N@Z=006bcf70
// @ref ?BuildingTypes@@3V?$DynamicVectorClass@PAVBuildingTypeClass@@@@A=00a35cd8

extern DynamicVectorClass<BuildingTypeClass *> BuildingTypes;      // 0x00A35CD8

void TeamClass::TMission_unknown_6be1c0(ScriptMissionClass const &mission, int unknown)
{
    FootClass *leader = unknown_func_6baa60();
    if (leader == 0) {
        StepCompleted = true;
        return;
    }
    HouseClass *house = leader->House;
    SuperClass *sphere = 0;
    SuperClass *warp = 0;
    for (int index = 0; index < house->Supers.Count(); index++) {
        if (house->Supers[index]->Type->Type == 3) {
            sphere = house->Supers[index];
        }
        if (house->Supers[index]->Type->Type == 4) {
            warp = house->Supers[index];
        }
    }
    if (sphere != 0 && warp != 0) {
        if (!sphere->unknown_0x57) {
            double remaining = sphere->RechargeTimer.Value();
            double total = sphere->Type->RechargeTime;
            if (sphere->unknown_0x55 && remaining / total <= 1.0f - Rules->unknown_b80) {
                return;
            }
            StepCompleted = true;
            return;
        }
        int value = (mission.Data >> 16) & 0xFFFF;
        BuildingTypeClass *type = BuildingTypes[mission.Data & 0xFFFF];
        HouseClass *enemy = 0;
        if (house->unknown_54f0 != -1) {
            enemy = Houses[house->unknown_54f0];
        }
        AbstractClass *target = Unknown_006BCF70(type, enemy, leader, value, Class->OnlyTargetHouseEnemy);
        if (target != 0) {
            house->unknown_func_4e68d0(sphere->Type->Type, Coord_Cell(unknown_34->Center_Coord()));
            house->unknown_func_4e68d0(warp->Type->Type, Coord_Cell(target->Center_Coord()));
            unknown_func_6b79e0(target);
        }
        StepCompleted = true;
        return;
    }
    StepCompleted = true;
}
