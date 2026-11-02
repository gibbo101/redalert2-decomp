// void TeamClass::TMission_unknown_6be440(ScriptMissionClass const &mission, bool unknown) (0x006BE440)
// Chronoshift to a target: with the leader house's super weapons of types 3 and 4 (hypothesis: ChronoSphere
// and ChronoWarp) and the first charged, the leader picks a target of the script argument's kind
// (0x006220E0, slot 219 from its position, the team type's OnlyTargetHouseEnemy); 3 fires at the team's
// cell (+0x34) and 4 at the target's, which becomes the team's target. Completes the step unless the first
// is present and still charging below the rules' AI ready fraction. The early leader exit and the named
// target kind give the original's tail sharing; the inline Position_Coord_004f3f40 site (with the other
// pending sites) keeps 0x006BDD80 out of line in the expanded leader search, as in 0x006BE1C0.
#include "shared/unit.hpp"
#include "shared/foot.hpp"
#include "shared/team.hpp"
#include "shared/team_type.hpp"
#include "shared/house.hpp"
#include "shared/super.hpp"
#include "shared/rules.hpp"
// @ref ?unknown_func_4e68d0@HouseClass@@QAE_NHABVCell@@@Z=004e68d0
// @ref ?Unknown_006220E0@@YIHH@Z=006220e0

void TeamClass::TMission_unknown_6be440(ScriptMissionClass const &mission, bool unknown)
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
        int target_data = Unknown_006220E0(mission.Data);
        AbstractClass *target = leader->unknown_slot219(target_data, &leader->Position_Coord_004f3f40(), Class->OnlyTargetHouseEnemy);
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
