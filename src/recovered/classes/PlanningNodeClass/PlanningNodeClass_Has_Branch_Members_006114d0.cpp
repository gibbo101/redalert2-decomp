#define RA2_COORD_EQUAL_MEMBER
// bool PlanningNodeClass::Has_Branch_Members() const (0x006114D0)
#include "shared/planning.hpp"

bool PlanningNodeClass::Has_Branch_Members() const
{
    return Branch.Count > 0;
}
