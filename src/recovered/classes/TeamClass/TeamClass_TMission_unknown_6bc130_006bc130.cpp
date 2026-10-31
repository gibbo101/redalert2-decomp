// void TeamClass::TMission_unknown_6bc130(ScriptMissionClass const &mission, bool unknown) (0x006BC130)
// Calls FootClass slot 295 on every member, then completes the step.
#include "shared/unit.hpp"
#include "shared/foot.hpp"
#include "shared/team.hpp"

void TeamClass::TMission_unknown_6bc130(ScriptMissionClass const &mission, bool unknown)
{
    for (FootClass *member = Member; member != 0; member = (FootClass *)member->unknown_4c8) {
        member->unknown_slot295();
    }
    StepCompleted = true;
}
