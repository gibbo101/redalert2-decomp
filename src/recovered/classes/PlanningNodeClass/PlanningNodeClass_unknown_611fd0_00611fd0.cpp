#define RA2_COORD_EQUAL_MEMBER
// void PlanningNodeClass::unknown_611fd0() (0x00611FD0)
// Finds the loop branch: the branch with the same origin coordinate as the
// node's own (loop) branch, or -1.
#include "shared/planning.hpp"

void PlanningNodeClass::unknown_611fd0()
{
    unknown_b0 = -1;
    if (Branch.Get_Count()) {
        EventClass event = Branch.Event;
        int branches = Branches.Count();
        for (int b = 0; b < branches; b++) {
            EventClass other = Branches[b]->Event;
            CoordStruct here = Planning_Event_Coord(event);
            CoordStruct there = Planning_Event_Coord(other);
            if (here == there) {
                unknown_b0 = b;
                return;
            }
        }
    }
}
