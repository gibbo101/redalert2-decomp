#define RA2_COORD_EQUAL_MEMBER
// int PlanningBranchClass::Decrement_Count() (0x00610900)
#include "shared/planning.hpp"

int PlanningBranchClass::Decrement_Count()
{
    return --Count;
}
