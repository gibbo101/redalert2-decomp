#define RA2_COORD_EQUAL_MEMBER
// TechnoClass *PlanningNodeClass::Branch_Owner(int index) const (0x00611500)
#include "shared/planning.hpp"

TechnoClass *PlanningNodeClass::Branch_Owner(int index) const
{
    for (int i = 0; i < Members.Count(); i++) {
        PlanningMemberClass *member = Members[i];
        if (member->BranchIndex == index) {
            return member->Owner;
        }
    }
    return 0;
}
