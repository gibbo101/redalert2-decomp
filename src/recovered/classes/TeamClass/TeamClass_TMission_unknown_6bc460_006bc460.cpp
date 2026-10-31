// void TeamClass::TMission_unknown_6bc460(ScriptMissionClass const &mission, bool unknown) (0x006BC460)
// Unless 0x0051FC50 reports its flag, calls 0x0051F930 with the line's data, a rules value and the zero cell, then completes the step.
#include "shared/unit.hpp"
#include "shared/foot.hpp"
#include "shared/team.hpp"
// @ref ?Unknown_0051FC50@@YA_NXZ=0051fc50
// @ref ?Unknown_0051F930@@YIXHHVCell@@H@Z=0051f930
// @ref _unknown_geometry_k=00ac0050
// @ref ?Rules@@3PAVRulesClass@@A=00839848

void TeamClass::TMission_unknown_6bc460(ScriptMissionClass const &mission, bool unknown)
{
    if (!Unknown_0051FC50()) {
        Unknown_0051F930(mission.Data, Rules->unknown_13e8, unknown_geometry_k, 0);
    }
    StepCompleted = true;
}
