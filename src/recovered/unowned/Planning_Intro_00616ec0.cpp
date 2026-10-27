#define RA2_COORD_EQUAL_MEMBER
// void __fastcall Planning_Intro(bool forced, bool first) (0x00616EC0)
// Shows a planning-mode introduction message: the first introduction (by
// button when forced, else by key) or the third; unless forced, each kind is
// shown once.
#include "shared/planning.hpp"
// @ref ?unknown_counts_a766b4@@3PAHA=00a766b4
// @ref ??_C@_0BH@EHFA@MSG?3PlanningModeIntro3?$AA@=007ebe0c
// @ref ??_C@_0BK@KLPP@MSG?3PlanningModeIntro1Key?$AA@=007ebe24
// @ref ??_C@_0BN@HKPN@MSG?3PlanningModeIntro1Button?$AA@=007ebe40

void __fastcall Planning_Intro(bool forced, bool first)
{
    int kind;
    if (first) {
        kind = !forced;
    } else {
        kind = 2;
    }
    int limit;
    if (forced) {
        limit = unknown_counts_a766b4[kind] + 1;
    } else {
        limit = 1;
    }
    if (unknown_counts_a766b4[kind] < limit) {
        if (first) {
            if (forced) {
                Planning_Message("MSG:PlanningModeIntro1Button");
            } else {
                Planning_Message("MSG:PlanningModeIntro1Key");
            }
        } else {
            Planning_Message("MSG:PlanningModeIntro3");
        }
        unknown_counts_a766b4[kind]++;
    }
}
