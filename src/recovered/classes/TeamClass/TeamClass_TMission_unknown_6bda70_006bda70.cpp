// void TeamClass::TMission_unknown_6bda70(ScriptMissionClass const &mission, bool unknown) (0x006BDA70)
// When flagged, calls 0x006D8FD0 for the first member with the line's data, then completes the step.
#include "shared/unit.hpp"
#include "shared/foot.hpp"
#include "shared/team.hpp"
// @ref ?Unknown_006D8FD0@@YIXPAVFootClass@@H@Z=006d8fd0

void TeamClass::TMission_unknown_6bda70(ScriptMissionClass const &mission, bool unknown)
{
    if (unknown) {
        Unknown_006D8FD0(Member, mission.Data);
        StepCompleted = true;
    }
}
