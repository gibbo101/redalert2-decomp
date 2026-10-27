#define RA2_COORD_EQUAL_MEMBER
// EventClass *PlanningMemberClass::Get_Event() const (0x00610850)
#include "shared/planning.hpp"

EventClass *PlanningMemberClass::Get_Event() const
{
    return Event;
}
