// void TeamClass::TMission_unknown_6bc5b0(ScriptMissionClass const &mission, bool unknown) (0x006BC5B0)
// Completes the step once every member holds as many passengers as its type carries (leaves it pending while any is short).
#include "shared/unit.hpp"
#include "shared/foot.hpp"
#include "shared/team.hpp"
#include "shared/techno_type.hpp"

void TeamClass::TMission_unknown_6bc5b0(ScriptMissionClass const &mission, bool unknown)
{
    for (FootClass *member = Member; member != 0; member = (FootClass *)member->unknown_4c8) {
        if (member->unknown_slot32()->Passengers > member->Cargo.Count) {
            return;
        }
    }
    StepCompleted = true;
}
