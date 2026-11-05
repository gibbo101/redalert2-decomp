#define RA2_COORD_EQUAL_MEMBER
// int __fastcall Planning_Order_Kind(TechnoClass *techno, PlanningEventTargets const *event) (0x00615A80)
// How an order relates to the techno's planned path: 0 for event types 6, 7
// and 9 or an order that keeps the techno in place; when the path's last node
// holds a terminating order for the techno (missions 7-9) 1, a move/attack
// order onto a cell or (mission 11) nowhere 2; else -1. Name hypothesis.
#include "shared/planning.hpp"
// @ref ?Planning_Order_Stays_Put@@YI_NPAVTechnoClass@@HVTargetClass@@@Z=00615910

int __fastcall Planning_Order_Kind(TechnoClass *techno, PlanningEventTargets const *event)
{
    if (Planning_Stop_Type(event->Type)) {
        return 0;
    }
    int order_mission = event->Mission();
    TargetClass const &target = event->Target();
    if (Planning_Order_Stays_Put(techno, order_mission, target)) {
        return 0;
    }
    PlanningTokenClass *token = Planning_Token(techno);
    if (token != 0 && token->Get_Node_Count() > 0) {
        EventClass last_event = token->Event_At(token->Get_Node_Count() - 1);
                PlanningEventTargets const *targets = (PlanningEventTargets const *)&last_event;
        int mission = targets->Mission();
        if (Planning_Terminal_Mission(mission)) {
            return 1;
        }
        if (Planning_Cell_Mission(mission, targets->Target())) {
            return 2;
        }
    }
    return -1;
}
