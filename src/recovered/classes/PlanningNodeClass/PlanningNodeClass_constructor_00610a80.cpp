#define RA2_COORD_EQUAL_MEMBER
// PlanningNodeClass::PlanningNodeClass(int unknown_18) (0x00610A80)
#include "shared/planning.hpp"

PlanningNodeClass::PlanningNodeClass(int unknown_18) :
    unknown_18(unknown_18),
    IsQueued(false),
    unknown_b0(-1),
    unknown_b4(-1)
{
}
