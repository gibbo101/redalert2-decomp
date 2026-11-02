#define RA2_COORD_EQUAL_MEMBER
// int __fastcall Planning_Event_Result(PlanningTokenClass *token, PlanningEventTargets const *event) (0x006171E0)
// What planning mode does with an order (the kinds of Planning_Refuse_Command):
// 0 for a terminating order (missions 7-9, or a move/attack whose target
// reference is of kind 11 or, for mission 11, empty), 2 when the token's path
// is full (15 nodes), else -1 (taken).
#include "shared/planning.hpp"

int __fastcall Planning_Event_Result(PlanningTokenClass *token, PlanningEventTargets const *event)
{
    int mission = (signed char)event->unknown_0c;
    TargetClass const &target_ref = event->Target_0e;
    bool terminating = mission == 7 || mission == 8 || mission == 9;
    if (terminating) {
        return 0;
    }
    TargetClass target = target_ref;
    bool cell = (mission == 1 || mission == 11) && (target.Kind == 11 || (mission == 11 && !target.Kind));
    if (cell) {
        return 0;
    }
    return token->Nodes.Count() == 15 ? 2 : -1;
}
