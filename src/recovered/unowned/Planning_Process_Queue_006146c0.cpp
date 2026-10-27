#define RA2_COORD_EQUAL_MEMBER
// void Planning_Process_Queue() (0x006146C0)
// Settles every queued node (rebuilds its branches) and empties the queue.
#include "shared/planning.hpp"

void Planning_Process_Queue()
{
    DynamicVectorClass<PlanningNodeClass *> &queue = PlanningNodeClass::unknown_list_00a76758;
    int count = queue.Count();
    for (int i = 0; i < count; i++) {
        queue[i]->unknown_611730();
    }
    queue.DynamicVectorClass<PlanningNodeClass *>::Clear();
}
