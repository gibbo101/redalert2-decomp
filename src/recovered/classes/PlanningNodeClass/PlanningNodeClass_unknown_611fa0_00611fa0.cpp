#define RA2_COORD_EQUAL_MEMBER
// void PlanningNodeClass::unknown_611fa0(PlanningMemberClass *member) (0x00611FA0)
// Takes a member out of the loop branch (the last one resets its index).
#include "shared/planning.hpp"

void PlanningNodeClass::unknown_611fa0(PlanningMemberClass *member)
{
    member->unknown_0c = false;
    if (--Branch.Count == 0) {
        unknown_b0 = -1;
    }
}
