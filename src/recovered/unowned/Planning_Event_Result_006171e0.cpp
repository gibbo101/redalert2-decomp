#define RA2_COORD_EQUAL_MEMBER
// int __fastcall Planning_Event_Result(PlanningTokenClass *token, PlanningEventTargets const *event) (0x006171E0)
// What planning mode does with an order (the kinds of Planning_Refuse_Command):
// 0 for a terminating order (missions 7-9, or a move/attack whose target
// reference is of kind 11 or, for mission 11, empty), 2 when the token's path
// is full (15 nodes), else -1 (taken).
#include "shared/planning.hpp"

int __fastcall Planning_Event_Result(PlanningTokenClass *token, PlanningEventTargets const *event)
{
    int mission = event->Mission();
    TargetClass const &target = event->Target();
    if (Planning_Terminal_Mission(mission)) {
        return 0;
    }
    if (Planning_Cell_Mission(mission, target)) {
        return 0;
    }
    if (token->Get_Node_Count() == 15) {
        return 2;
    }
    return -1;
}
