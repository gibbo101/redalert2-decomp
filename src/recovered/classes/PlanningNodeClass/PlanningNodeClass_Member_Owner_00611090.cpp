#define RA2_COORD_EQUAL_MEMBER
// TechnoClass *PlanningNodeClass::Member_Owner(int index) const (0x00611090)
#include "shared/planning.hpp"

TechnoClass *PlanningNodeClass::Member_Owner(int index) const
{
    PlanningMemberClass *member = Members[index];
    TechnoClass *owner = member->Owner;
    return owner;
}
