#define RA2_COORD_EQUAL_MEMBER
// void Planning_Refuse_No_Guard_Area() (0x00616E70)
// Planning mode cannot take an area guard order.
#include "shared/planning.hpp"
// @ref ??_C@_0BM@OHB@MSG?3PlanningModeNoGuardArea?$AA@=007ebdf0

void __fastcall Planning_Refuse_No_Guard_Area()
{
    Planning_Refuse("MSG:PlanningModeNoGuardArea");
}
