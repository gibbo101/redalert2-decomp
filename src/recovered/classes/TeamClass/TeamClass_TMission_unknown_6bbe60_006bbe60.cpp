// void TeamClass::TMission_unknown_6bbe60(ScriptMissionClass const &mission, int unknown) (0x006BBE60)
// Sets local variable Data.
#include "shared/unit.hpp"
#include "shared/foot.hpp"
#include "shared/team.hpp"
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref ?unknown_6612c0@UnknownIDSource@@QAE_NI_N@Z=006612c0

void TeamClass::TMission_unknown_6bbe60(ScriptMissionClass const &mission, int unknown)
{
    unknown_id_source_a3d290->unknown_6612c0(mission.Data, true);
    StepCompleted = true;
}
