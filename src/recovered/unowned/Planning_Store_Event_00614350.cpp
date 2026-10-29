#define RA2_COORD_EQUAL_MEMBER
// void __fastcall Planning_Store_Event(EventClass const &event) (0x00614350)
// Lists a copy of an event among the planned events (0x00A76648); a copied
// mission event (type 4) is marked 2 at +0x1D. Name hypothesis; no callers.
#include "shared/planning.hpp"

void __fastcall Planning_Store_Event(EventClass const &event)
{
    EventClass *copy = new EventClass;
    *copy = event;
    if (copy->Type == 4) {
        ((PlanningEventTargets *)copy)->unknown_1d = 2;
    }
    PlanningLists::unknown_list_00a76648.Add(copy);
}
