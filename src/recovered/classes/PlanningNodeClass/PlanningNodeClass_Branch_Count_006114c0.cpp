#define RA2_COORD_EQUAL_MEMBER
// int PlanningNodeClass::Branch_Count() const (0x006114C0)
#include "shared/planning.hpp"

int PlanningNodeClass::Branch_Count() const
{
    return Branches.Count();
}
