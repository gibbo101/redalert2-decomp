// void TeamClass::TMission_unknown_6bb350(ScriptMissionClass const &mission, bool unknown) (0x006BB350)
// Calls FootClass slot 222 on every member with the house of type Data (and 1), then completes the step.
#include "shared/unit.hpp"
#include "shared/foot.hpp"
#include "shared/team.hpp"
#include "shared/house.hpp"
// @ref ?As_Pointer@HouseClass@@SIPAV1@H@Z=004ed760

void TeamClass::TMission_unknown_6bb350(ScriptMissionClass const &mission, bool unknown)
{
    FootClass *member = Member;
    while (member != 0) {
        FootClass *next = (FootClass *)member->unknown_4c8;
        member->unknown_slot222(HouseClass::As_Pointer(mission.Data), 1);
        member = next;
    }
    StepCompleted = true;
}
