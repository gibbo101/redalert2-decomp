#define RA2_COORD_EQUAL_MEMBER
// void PlanningNodeClass::unknown_611730() (0x00611730)
#include "shared/planning.hpp"

void PlanningNodeClass::unknown_611730()
{
    unknown_611ee0();
    int count = Members.Count();
    for (int i = 0; i < count; i++) {
        unknown_611bd0(Members[i]);
    }
    unknown_611770();
    IsQueued = false;
}
