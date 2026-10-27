// void TeamClass::TMission_unknown_6bc6d0(ScriptMissionClass const &mission, bool unknown) (0x006BC6D0)
// Picks a target of a building type (Data: type index in the low word, a
// value in the high word) for the first member, then waits until every
// member has ammo and completes the step.
#include "shared/unit.hpp"
#include "shared/foot.hpp"
#include "shared/team.hpp"
#include "shared/team_type.hpp"
#include "shared/techno_type.hpp"
#include "shared/house.hpp"
// @ref ?Unknown_006BCF70@@YIPAVAbstractClass@@PAVBuildingTypeClass@@PAVHouseClass@@PAVFootClass@@H_N@Z=006bcf70
// @ref ?unknown_func_6b79e0@TeamClass@@QAEXPAVAbstractClass@@@Z=006b79e0
// @ref ?unknown_func_6b9bb0@TeamClass@@QAEXXZ=006b9bb0
// @ref ?BuildingTypes@@3V?$DynamicVectorClass@PAVBuildingTypeClass@@@@A=00a35cd8
// @ref ?Houses@@3V?$DynamicVectorClass@PAVHouseClass@@@@A=00a32298

extern DynamicVectorClass<BuildingTypeClass *> BuildingTypes;      // 0x00A35CD8

void TeamClass::TMission_unknown_6bc6d0(ScriptMissionClass const &mission, bool unknown)
{
    if (unknown && unknown_3c == 0 && Member != 0) {
        FootClass *first = Member;
        int value = (mission.Data >> 16) & 0xFFFF;
        BuildingTypeClass *type = BuildingTypes[mission.Data & 0xFFFF];
        HouseClass *enemy = 0;
        if (first->House->unknown_54f0 != -1) {
            enemy = Houses[first->House->unknown_54f0];
        }
        AbstractClass *target = Unknown_006BCF70(type, enemy, first, value, Class->OnlyTargetHouseEnemy);
        if (target != 0) {
            unknown_func_6b79e0(target);
        }
    }
    if (unknown_3c != 0) {
        for (FootClass *member = Member; member != 0; member = (FootClass *)member->unknown_4c8) {
            if (member->unknown_slot32()->Ammo <= 0 || member->unknown_254 > 0) {
                unknown_func_6b9bb0();
                return;
            }
        }
    }
    unknown_func_6b79e0(0);
    StepCompleted = true;
}

