// void TeamClass::TMission_unknown_6bc260(ScriptMissionClass const &mission, int unknown) (0x006BC260)
// Plays the sound named by the line at full volume, then completes the step.
#include "shared/unit.hpp"
#include "shared/foot.hpp"
#include "shared/team.hpp"

void TeamClass::TMission_unknown_6bc260(ScriptMissionClass const &mission, int unknown)
{
    Voc_Play(mission.Data, 1.0f, 0x2000, 0);
    StepCompleted = true;
}
