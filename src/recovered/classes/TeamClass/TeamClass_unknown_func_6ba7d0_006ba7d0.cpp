// For a live member that is not yet in place: when it is farther from the team's object (+0x34) than the allowed distance, sends it toward it (guard mission 2, no target, destination +0x34) and returns true; otherwise flags it in place.
#include "shared/unit.hpp"
#include "shared/foot.hpp"
#include "shared/team.hpp"
// @ref ?unknown_a40774@@3HA=00a40774
// @ref ?Get_Current_Mission@ScriptClass@@QBE?AVScriptMissionClass@@XZ=00668870
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?unknown_5d4c00@ObjectClass@@QAEHPAVAbstractClass@@@Z=005d4c00

bool TeamClass::unknown_func_6ba7d0(FootClass *member)
{
    if (unknown_func_6bdd80(member) && !member->unknown_579) {
        if (member->unknown_5d4c00(unknown_34) > Unknown_006BE6A0()) {
            if (member->unknown_494 == 0) {
                member->unknown_slot116(2, false);
                member->unknown_slot220(0);
                member->unknown_slot260(unknown_34, 1);
            }
            return true;
        }
        member->unknown_579 = true;
    }
    return false;
}
