#define RA2_COORD_EQUAL_MEMBER
// PlanningBranchClass *PlanningNodeClass::Own_Branch() (0x006115C0)
#include "shared/planning.hpp"

PlanningBranchClass *PlanningNodeClass::Own_Branch()
{
    return &Branch;
}
