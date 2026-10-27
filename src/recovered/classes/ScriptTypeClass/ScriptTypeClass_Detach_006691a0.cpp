// void ScriptTypeClass::Detach(AbstractClass *target, bool all) (0x006691A0)
// When a team type goes away, lines with action 0x12 that name a later team
// type index move down by one; lines naming it fall back to 0.
#include "shared/script.hpp"
// @ref ?TeamTypes@@3V?$DynamicVectorClass@PAVTeamTypeClass@@@@A=00a40c48

void ScriptTypeClass::Detach(AbstractClass *target, bool all)
{
    if (target != 0 && target->Kind_Of() == 0x23) {
        int index = -1;
        for (int line = 0; line < MissionCount; line++) {
            if (MissionList[line].Mission == 0x12) {
                if (index == -1) {
                    index = TeamTypes.ID((TeamTypeClass *)target);
                    if (index == -1) {
                        return;
                    }
                }
                if (MissionList[line].Data > index) {
                    MissionList[line].Data--;
                } else if (MissionList[line].Data == index) {
                    MissionList[line].Data = 0;
                }
            }
        }
    }
}
