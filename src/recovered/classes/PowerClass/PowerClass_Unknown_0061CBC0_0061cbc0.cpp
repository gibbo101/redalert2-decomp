// void PowerClass::Unknown_0061CBC0() (0x0061CBC0)
// Steps one of the power bar's counters up toward the target 0x0061C700
// gives it: +0x1530 first, then +0x1528, then +0x152C (the counterpart of
// 0x0061CB50; no direct callers).
#include "shared/power.hpp"
// @ref ?Unknown_0061C700@PowerClass@@QAEHAAH00@Z=0061c700

void PowerClass::Unknown_0061CBC0()
{
    int target_1528;
    int target_1530;
    int target_152c;
    Unknown_0061C700(target_1528, target_152c, target_1530);
    if (unknown_1530 < target_1530) {
        unknown_1530++;
        return;
    }
    if (unknown_1528 < target_1528) {
        unknown_1528++;
        return;
    }
    if (unknown_152c < target_152c) {
        unknown_152c++;
    }
}
