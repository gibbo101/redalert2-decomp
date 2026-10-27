#define RA2_COORD_EQUAL_MEMBER
// void PlanningNodeClass::unknown_611440() (0x00611440)
#include "shared/planning.hpp"

void PlanningNodeClass::unknown_611440()
{
    int count = Members.Count();
    for (int index = 0; index < count; index++) {
        PlanningEventTargets *event = (PlanningEventTargets *)Members[index]->Event;
        if (event->unknown_0c == 2) {
            event->unknown_0c = 0x1D;
        }
    }
}
