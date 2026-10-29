#define RA2_COORD_EQUAL_MEMBER
// void __fastcall Planning_Refuse_Order(EventClass const *event) (0x00617020)
// Shows the refusal for an order planning mode cannot take: deploy (event
// type 9), stop (6) or scatter (7). Name hypothesis; no callers.
#include "shared/planning.hpp"
// @ref ??_C@_0BJ@KJDB@MSG?3PlanningModeNoDeploy?$AA@=007ebda4
// @ref ??_C@_0BH@OJOH@MSG?3PlanningModeNoStop?$AA@=007ebd8c
// @ref ??_C@_0BK@LLNH@MSG?3PlanningModeNoScatter?$AA@=007ebd70

void __fastcall Planning_Refuse_Order(EventClass const *event)
{
    if (event->Type == 9) {
        Planning_Refuse("MSG:PlanningModeNoDeploy");
    } else if (event->Type == 6) {
        Planning_Refuse("MSG:PlanningModeNoStop");
    } else if (event->Type == 7) {
        Planning_Refuse("MSG:PlanningModeNoScatter");
    }
}
