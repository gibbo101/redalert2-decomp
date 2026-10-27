// Sets the team's target (+0x3C, with +0x40 following it when unset or equal), first sending members that were working on the old target back to guard; a cell target (kind 0x0B) not on the map flags +0x81 and sends the members to it.
#include "shared/unit.hpp"
#include "shared/foot.hpp"
#include "shared/team.hpp"
#include "shared/map_view.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0

void TeamClass::unknown_func_6b79e0(AbstractClass *target)
{
    if (target != unknown_3c) {
        FootClass *member = Member;
        if (unknown_3c != 0) {
            for (; member != 0; member = (FootClass *)member->unknown_4c8) {
                bool target_hit = member->unknown_228 == unknown_3c;
                bool destination_hit = member->unknown_494 == unknown_3c;
                if (target_hit || destination_hit) {
                    member->unknown_slot116(5, false);
                    if (destination_hit) {
                        member->unknown_slot260(0, 1);
                    }
                    if (target_hit) {
                        member->unknown_slot220(0);
                    }
                }
            }
        }
    }
    if (unknown_40 == unknown_3c || unknown_40 == 0) {
        unknown_40 = target;
    }
    unknown_3c = target;
    if (target != 0 && target->Kind_Of() == 0xB) {
        if (!Map.Unknown_0055A740((CellClass *)target, 1)) {
            TargetNotAssigned = true;
            for (FootClass *member = Member; member != 0; member = (FootClass *)member->unknown_4c8) {
                member->unknown_slot260(0, 1);
            }
        } else {
            TargetNotAssigned = false;
        }
    }
}
