// Red Alert's Lagging_Units: while the team is lagging, every live, placed member farther from the team's object (+0x38) than the allowed distance (tripled for aircraft, a third for non-guarding members of guard-slower teams) is sent toward it, the others are put back to guard (mission 5); stores and returns whether any lags.
#include "shared/unit.hpp"
#include "shared/foot.hpp"
#include "shared/team.hpp"
#include "shared/team_type.hpp"
// @ref ?unknown_a40774@@3HA=00a40774
// @ref ?Get_Current_Mission@ScriptClass@@QBE?AVScriptMissionClass@@XZ=00668870
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?unknown_sqrt_4ba410@@YANN@Z=004ba410

bool TeamClass::unknown_func_6ba600()
{
    FootClass *member = Member;
    bool lagging = false;
    if (!IsLagging) {
        return false;
    }
    for (; member != 0; member = (FootClass *)member->unknown_4c8) {
        if (unknown_func_6bdd80(member) && (member->unknown_579 || member->Kind_Of() == 2)) {
            int allowed = Unknown_006BE6A0();
            if (member->Kind_Of() == 2) {
                allowed *= 3;
            }
            if (Class->GuardSlower && !member->unknown_slot283()) {
                allowed /= 3;
            }
            if (Coord_Length(member->Center_Coord() - unknown_38->Center_Coord()) > allowed) {
                if (member->unknown_494 == 0) {
                    member->unknown_slot116(2, false);
                    member->unknown_slot260(unknown_38, 1);
                }
                lagging = true;
            } else if (member->unknown_slot91() != 5) {
                member->unknown_slot116(5, false);
                member->unknown_slot260(0, 1);
            }
        }
    }
    IsLagging = lagging;
    return lagging;
}
