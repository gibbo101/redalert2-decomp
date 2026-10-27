#define RA2_COORD_EQUAL_MEMBER
// void PlanningNodeClass::Set_Queued() (0x00611710)
#include "shared/planning.hpp"

void PlanningNodeClass::Set_Queued()
{
    IsQueued = true;
}
