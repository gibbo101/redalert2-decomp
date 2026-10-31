// void TeamClass::TMission_unknown_6bc3a0(ScriptMissionClass const &mission, bool unknown) (0x006BC3A0)
// Kills every member that is alive and on the map (slot 86 with the rules' warhead), repeating while any was hit, then completes the step.
#include "shared/unit.hpp"
#include "shared/foot.hpp"
#include "shared/team.hpp"

void TeamClass::TMission_unknown_6bc3a0(ScriptMissionClass const &mission, bool unknown)
{
    bool hit;
    do {
        hit = false;
        for (FootClass *member = Member; member != 0; member = (FootClass *)member->unknown_4c8) {
            if (member->Strength > 0 && member->unknown_7d && member->unknown_74 && !member->unknown_76) {
                int damage = member->Strength;
                member->unknown_slot86(&damage, 0, Rules->unknown_c74, 0, true, 0);
                hit = true;
            }
        }
    } while (hit);
    StepCompleted = true;
}
