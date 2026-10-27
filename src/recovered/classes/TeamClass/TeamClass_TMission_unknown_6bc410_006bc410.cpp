// void TeamClass::TMission_unknown_6bc410(ScriptMissionClass const &mission, int unknown) (0x006BC410)
// Takes every member off the map (slot 52) and removes it (slot 60), then completes the step.
#include "shared/unit.hpp"
#include "shared/foot.hpp"
#include "shared/team.hpp"

void TeamClass::TMission_unknown_6bc410(ScriptMissionClass const &mission, int unknown)
{
    FootClass *member = Member;
    while (member != 0) {
        FootClass *next = (FootClass *)member->unknown_4c8;
        member->unknown_slot52();
        member->unknown_slot60();
        member = next;
    }
    StepCompleted = true;
}
