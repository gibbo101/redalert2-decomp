// void TeamClass::TMission_unknown_6bc290(ScriptMissionClass const &mission, int unknown) (0x006BC290)
// Calls 0x005A07F0 with the line's data, -1 and three ones, then completes the step.
#include "shared/unit.hpp"
#include "shared/foot.hpp"
#include "shared/team.hpp"
// @ref ?Unknown_005A07F0@@YIXHHHHH@Z=005a07f0

void TeamClass::TMission_unknown_6bc290(ScriptMissionClass const &mission, int unknown)
{
    Unknown_005A07F0(mission.Data, -1, 1, 1, 1);
    StepCompleted = true;
}
