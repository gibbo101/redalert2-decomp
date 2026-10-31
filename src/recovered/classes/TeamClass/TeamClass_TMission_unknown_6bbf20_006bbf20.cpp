// void TeamClass::TMission_unknown_6bbf20(ScriptMissionClass const &mission, bool unknown) (0x006BBF20)
// Re-picks the team's targets (+0x34/+0x38 through 0x006B9610), copies +0x34 to +0x40, runs 0x006BA1A0, and then points every live, placed member at the new target's own target.
#include "shared/unit.hpp"
#include "shared/foot.hpp"
#include "shared/team.hpp"
// @ref ?unknown_func_6b9610@TeamClass@@QAEXPAPAVAbstractClass@@0@Z=006b9610
// @ref ?unknown_func_6ba1a0@TeamClass@@QAEXXZ=006ba1a0
// @ref ?As_Techno@AbstractClass@@QAEPAVTechnoClass@@XZ=0040dc20
// @ref ?unknown_a40774@@3HA=00a40774

void TeamClass::TMission_unknown_6bbf20(ScriptMissionClass const &mission, bool unknown)
{
    unknown_func_6b9610(&unknown_34, &unknown_38);
    unknown_40 = unknown_34;
    unknown_func_6ba1a0();
    TechnoClass *target = unknown_34->As_Techno();
    if (target != 0) {
        for (FootClass *member = Member; member != 0; member = (FootClass *)member->unknown_4c8) {
            if (unknown_func_6bdd80(member) && (member->unknown_579 || member->Kind_Of() == 2)) {
                if (member->unknown_228 != 0 && member->unknown_228 != target->unknown_228) {
                    member->unknown_slot220(0);
                }
                if (target->unknown_228 != 0) {
                    if (!member->Locomotor.Checked()->Is_Moving() && member->unknown_slot163() && member->unknown_slot91() == 5) {
                        member->unknown_slot116(1, false);
                        member->unknown_slot220(target->unknown_228);
                    }
                }
            }
        }
    }
}
