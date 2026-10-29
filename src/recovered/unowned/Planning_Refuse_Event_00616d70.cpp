#define RA2_COORD_EQUAL_MEMBER
// void __fastcall Planning_Refuse_Event(EventClass const *event) (0x00616D70)
// Shows the refusal for an order planning mode cannot take (deploy, stop or
// scatter, as 0x00617020) and plays the refused-action sound.
#include "shared/planning.hpp"
// @ref ??_C@_0BJ@KJDB@MSG?3PlanningModeNoDeploy?$AA@=007ebda4
// @ref ??_C@_0BH@OJOH@MSG?3PlanningModeNoStop?$AA@=007ebd8c
// @ref ??_C@_0BK@LLNH@MSG?3PlanningModeNoScatter?$AA@=007ebd70
// @ref ?Rules@@3PAVRulesClass@@A=00839848

void __fastcall Planning_Refuse_Event(EventClass const *event)
{
    if (event->Type == 9) {
        Planning_Refuse("MSG:PlanningModeNoDeploy");
    } else if (event->Type == 6) {
        Planning_Refuse("MSG:PlanningModeNoStop");
    } else if (event->Type == 7) {
        Planning_Refuse("MSG:PlanningModeNoScatter");
    }
    Voc_Play(Rules->unknown_620, 1.0f, 0x2000, 0);
}
