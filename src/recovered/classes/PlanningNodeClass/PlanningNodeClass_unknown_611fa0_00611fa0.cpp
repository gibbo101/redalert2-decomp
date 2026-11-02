#define RA2_COORD_EQUAL_MEMBER
// void PlanningNodeClass::unknown_611fa0(PlanningMemberClass *member) (0x00611FA0)
// Takes a member out of the loop branch (the last one resets its index).
// Written through the member and branch accessors: the accessor form's size
// makes /Ob2 charge this body where it is expanded, as the original's
// inlining decisions in 0x00610E70 require.
#include "shared/planning.hpp"

void PlanningNodeClass::unknown_611fa0(PlanningMemberClass *member)
{
    member->Set_unknown_0c(false);
    Branch.Set_Count(Branch.Get_Count() - 1);
    if (Branch.Get_Count() == 0) {
        unknown_b0 = -1;
    }
}
