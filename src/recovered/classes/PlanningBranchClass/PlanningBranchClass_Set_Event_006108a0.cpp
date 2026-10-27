#define RA2_COORD_EQUAL_MEMBER
// void PlanningBranchClass::Set_Event(EventClass const &event) (0x006108A0)
#include "shared/planning.hpp"

void PlanningBranchClass::Set_Event(EventClass const &event)
{
    Event = event;
}
