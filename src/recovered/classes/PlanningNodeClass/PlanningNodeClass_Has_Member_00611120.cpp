#define RA2_COORD_EQUAL_MEMBER
// bool PlanningNodeClass::Has_Member(TechnoClass *techno) const (0x00611120)
#include "shared/planning.hpp"

bool PlanningNodeClass::Has_Member(TechnoClass *techno) const
{
    return Member_Index(techno) != -1;
}
