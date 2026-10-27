#define RA2_COORD_EQUAL_MEMBER
// void Planning_Clear_Drawn() (0x00615BC0)
// Empties the list of nodes drawn on screen (unknown_list_00a766d8).
#include "shared/planning.hpp"

void Planning_Clear_Drawn()
{
    PlanningNodeClass::unknown_list_00a766d8.DynamicVectorClass<PlanningNodeClass *>::Clear();
}
