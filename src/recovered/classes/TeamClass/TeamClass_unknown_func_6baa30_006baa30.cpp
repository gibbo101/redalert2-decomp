// Clears the team's target and clears every member's target, flagging it.
#include "shared/unit.hpp"
#include "shared/foot.hpp"
#include "shared/team.hpp"
// @ref ?unknown_func_6b79e0@TeamClass@@QAEXPAVAbstractClass@@@Z=006b79e0

void TeamClass::unknown_func_6baa30()
{
    unknown_func_6b79e0(0);
    for (FootClass *member = Member; member != 0; member = (FootClass *)member->unknown_4c8) {
        member->unknown_slot220(0);
        member->unknown_578 = true;
    }
}
