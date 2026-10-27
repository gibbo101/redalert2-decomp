// void TeamClass::TMission_unknown_6bc2e0(ScriptMissionClass const &mission, int unknown) (0x006BC2E0)
// Calls 0x0055D990 on the cell of every member, then completes the step.
#include "shared/unit.hpp"
#include "shared/foot.hpp"
#include "shared/team.hpp"
#include "shared/map_view.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Unknown_0055D990@MapClass@@QAEXABVCell@@@Z=0055d990

void TeamClass::TMission_unknown_6bc2e0(ScriptMissionClass const &mission, int unknown)
{
    for (FootClass *member = Member; member != 0; member = (FootClass *)member->unknown_4c8) {
        Map.Unknown_0055D990(Coord_Cell(member->Center_Coord()));
    }
    StepCompleted = true;
}
