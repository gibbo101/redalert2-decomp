// void TeamClass::TMission_unknown_6bc4a0(ScriptMissionClass const &mission, bool unknown) (0x006BC4A0)
// Runs 0x0051FBB0 when 0x0051FC50 reports its flag, then completes the step.
#include "shared/unit.hpp"
#include "shared/foot.hpp"
#include "shared/team.hpp"
// @ref ?Unknown_0051FC50@@YA_NXZ=0051fc50
// @ref ?Unknown_0051FBB0@@YAXXZ=0051fbb0

void TeamClass::TMission_unknown_6bc4a0(ScriptMissionClass const &mission, bool unknown)
{
    if (Unknown_0051FC50()) {
        Unknown_0051FBB0();
    }
    StepCompleted = true;
}
