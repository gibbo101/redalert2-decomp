// void TeamClass::TMission_unknown_6bd7f0(ScriptMissionClass const &mission, bool unknown) (0x006BD7F0)
// Completes the step and sets IsSuspended.
#include "shared/team.hpp"

void TeamClass::TMission_unknown_6bd7f0(ScriptMissionClass const &mission, bool unknown)
{
    StepCompleted = true;
    IsSuspended = true;
}
