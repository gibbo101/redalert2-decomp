#define RA2_COORD_EQUAL_MEMBER
// void __stdcall Planning_Send_Event(EventClass event) (0x00614B70)
// A mission event (type 4) is marked as planned and queued for sending.
#include "shared/planning.hpp"

void __stdcall Planning_Send_Event(EventClass event)
{
    if (event.Type == 4) {
        ((PlanningEventTargets *)&event)->unknown_1d = 1;
        Unknown_0062E670(event);
    }
}
