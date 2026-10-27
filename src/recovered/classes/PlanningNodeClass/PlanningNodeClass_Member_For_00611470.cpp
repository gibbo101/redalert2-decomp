#define RA2_COORD_EQUAL_MEMBER
// PlanningMemberClass *PlanningNodeClass::Member_For(TechnoClass *techno) const (0x00611470)
#include "shared/planning.hpp"

PlanningMemberClass *PlanningNodeClass::Member_For(TechnoClass *techno) const
{
    int index = Member_Index(techno);
    if (index == -1) {
        return 0;
    }
    return Members[index];
}
