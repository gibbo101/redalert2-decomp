// void TeamClass::TMission_unknown_6bbb40(ScriptMissionClass const &mission, bool unknown) (0x006BBB40)
// Waits Data * 15 frames: when flagged starts the timer, runs 0x006B9F40, and completes the step once the timer has run out.
#include "shared/unit.hpp"
#include "shared/foot.hpp"
#include "shared/team.hpp"
// @ref ?unknown_func_6b9f40@TeamClass@@QAEXXZ=006b9f40
// @ref ?Frame@@3HA=00a40d2c

void TeamClass::TMission_unknown_6bbb40(ScriptMissionClass const &mission, bool unknown)
{
    if (unknown) {
        unknown_58 = CDTimerClass<FrameTimerClass>(mission.Data * 15);
    }
    unknown_func_6b9f40();
    if (unknown_58.Value() == 0) {
        StepCompleted = true;
    }
}
