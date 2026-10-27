// void TeamClass::TMission_unknown_6bc380(ScriptMissionClass const &mission, int unknown) (0x006BC380)
// Sets the team type owner's +0x198 to 4.
#include "shared/unit.hpp"
#include "shared/foot.hpp"
#include "shared/team.hpp"
#include "shared/team_type.hpp"
#include "shared/house.hpp"

void TeamClass::TMission_unknown_6bc380(ScriptMissionClass const &mission, int unknown)
{
    Class->Owner->unknown_198 = 4;
    StepCompleted = true;
}
