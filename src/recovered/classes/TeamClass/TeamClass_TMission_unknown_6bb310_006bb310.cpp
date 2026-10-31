// void TeamClass::TMission_unknown_6bb310(ScriptMissionClass const &mission, bool unknown) (0x006BB310)
// Calls ObjectClass slot 87 (forced) with the zero coordinate on every member, then completes the step.
#include "shared/unit.hpp"
#include "shared/foot.hpp"
#include "shared/team.hpp"
// @ref _unknown_geometry_l=00ac0070

void TeamClass::TMission_unknown_6bb310(ScriptMissionClass const &mission, bool unknown)
{
    for (FootClass *member = Member; member != 0; member = (FootClass *)member->unknown_4c8) {
        member->unknown_slot87(unknown_geometry_l, true, false);
    }
    StepCompleted = true;
}
