#define RA2_COORD_EQUAL_MEMBER
// void __fastcall Planning_Help(int kind) (0x00616F50)
// Shows a planning-mode help message the first time it is wanted: the loop
// help (kind 3) or the delete help (kind 4).
#include "shared/planning.hpp"
// @ref ?unknown_counts_a766b4@@3PAHA=00a766b4
// @ref ??_C@_0BJ@GOOM@MSG?3PlanningModeLoopHelp?$AA@=007ebe7c
// @ref ??_C@_0BL@KBLM@MSG?3PlanningModeDeleteHelp?$AA@=007ebe60

void __fastcall Planning_Help(int kind)
{
    if (unknown_counts_a766b4[kind] < 1) {
        if (kind == 3) {
            Planning_Message("MSG:PlanningModeLoopHelp");
        } else if (kind == 4) {
            Planning_Message("MSG:PlanningModeDeleteHelp");
        }
        unknown_counts_a766b4[kind]++;
    }
}
