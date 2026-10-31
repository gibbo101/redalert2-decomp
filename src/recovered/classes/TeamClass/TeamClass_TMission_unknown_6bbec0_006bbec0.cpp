// void TeamClass::TMission_unknown_6bbec0(ScriptMissionClass const &mission, bool unknown) (0x006BBEC0)
// Sets global variable Data.
#include "shared/unit.hpp"
#include "shared/foot.hpp"
#include "shared/team.hpp"
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref ?unknown_661560@UnknownIDSource@@QAE_NI_N@Z=00661560

void TeamClass::TMission_unknown_6bbec0(ScriptMissionClass const &mission, bool unknown)
{
    unknown_id_source_a3d290->unknown_661560(mission.Data, true);
    StepCompleted = true;
}
