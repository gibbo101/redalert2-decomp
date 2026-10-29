// void TeamClass::TMission_unknown_6bc070(ScriptMissionClass const &mission, int unknown) (0x006BC070)
// Waits until no member is moving, turning idle members toward direction Data (Data << 13 in the 16-bit facing).
#include "shared/unit.hpp"
#include "shared/foot.hpp"
#include "shared/team.hpp"
// @ref ?Current@FacingClass@@QBE?AUUnknownFacingDir@@XZ=004b8be0
// @ref ?_com_issue_error@@YGXJ@Z=00795940

void TeamClass::TMission_unknown_6bc070(ScriptMissionClass const &mission, int unknown)
{
    bool done = true;
    FootClass *member = Member;
    if (member != 0) {
        do {
            if (member->Locomotor.Checked()->Is_Moving()) {
                done = false;
            } else {
                int facing = mission.Data;
                if (member->unknown_2e0.Current().Raw != (unsigned short)(facing << 13)) {
                    member->Locomotor.Checked()->Do_Turn(Facing_Dir(mission.Data));
                }
            }
            member = (FootClass *)member->unknown_4c8;
        } while (member != 0);
        if (!done) {
            return;
        }
    }
    StepCompleted = true;
}
