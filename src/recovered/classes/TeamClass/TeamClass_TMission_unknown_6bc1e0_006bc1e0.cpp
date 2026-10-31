// void TeamClass::TMission_unknown_6bc1e0(ScriptMissionClass const &mission, bool unknown) (0x006BC1E0)
// Moves the script to line mission.Data - 2 (the step after it advances to
// Data - 1) and completes the step.
#include "shared/team.hpp"
#include "shared/script.hpp"
// @ref ?Set_Mission@ScriptClass@@QAE_NH@Z=00668910

void TeamClass::TMission_unknown_6bc1e0(ScriptMissionClass const &mission, bool unknown)
{
    Script->Set_Mission(mission.Data - 2);
    StepCompleted = true;
}
