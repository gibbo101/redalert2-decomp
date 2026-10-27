#define RA2_COORD_EQUAL_MEMBER
// EventClass PlanningNodeClass::Event_For(TechnoClass *techno) const (0x006110D0)
#include "shared/planning.hpp"

EventClass PlanningNodeClass::Event_For(TechnoClass *techno) const
{
    return *Member_For(techno)->Event;
}
