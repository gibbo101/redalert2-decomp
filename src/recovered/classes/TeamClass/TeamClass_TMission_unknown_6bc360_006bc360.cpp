// void TeamClass::TMission_unknown_6bc360(ScriptMissionClass const &mission, bool unknown) (0x006BC360)
// Sets the team type owner's +0x136 flag.
#include "shared/unit.hpp"
#include "shared/foot.hpp"
#include "shared/team.hpp"
#include "shared/team_type.hpp"
#include "shared/house.hpp"

void TeamClass::TMission_unknown_6bc360(ScriptMissionClass const &mission, bool unknown)
{
    Class->Owner->unknown_136 = true;
    StepCompleted = true;
}
