#define RA2_COORD_EQUAL_MEMBER
// EventClass PlanningNodeClass::Member_Event(int index) const (0x006110A0)
#include "shared/planning.hpp"

EventClass PlanningNodeClass::Member_Event(int index) const
{
    return *Members[index]->Event;
}
