#define RA2_COORD_EQUAL_MEMBER
// TechnoClass *PlanningNodeClass::First_Counted_Owner() const (0x00611530)
#include "shared/planning.hpp"

TechnoClass *PlanningNodeClass::First_Counted_Owner() const
{
    for (int i = 0; i < Members.Count(); i++) {
        PlanningMemberClass *member = Members[i];
        if (member->unknown_0c) {
            return member->Owner;
        }
    }
    return 0;
}
