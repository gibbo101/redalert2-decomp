#define RA2_COORD_EQUAL_MEMBER
// int PlanningNodeClass::Member_Index(TechnoClass *techno) const (0x00611050)
#include "shared/planning.hpp"

int PlanningNodeClass::Member_Index(TechnoClass *techno) const
{
    int result = -1;
    for (int index = 0; index < Members.Count(); index++) {
        if (Members[index]->Owner == techno) {
            result = index;
            break;
        }
    }
    return result;
}
