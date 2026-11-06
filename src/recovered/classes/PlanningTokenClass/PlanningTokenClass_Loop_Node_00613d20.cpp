// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright 2026 ra2-decomp contributors
// Copyright 2025 Electronic Arts Inc.; 2026 OpenTS contributors
// Derived from Electronic Arts source code; EA's GPL Section 7 terms apply (COPYING.md).
#define RA2_COORD_EQUAL_MEMBER
// PlanningNodeClass *PlanningTokenClass::Loop_Node() (0x00613D20)
// Adopted from ra2-decomp PlanningTokenClass::Loop_Node (YR 0x00636F80).
// The node the path loops back to, or 0 without a loop.
#include "shared/planning.hpp"
// @ref ?Loop_Node@PlanningTokenClass@@QAEPAVPlanningNodeClass@@XZ=00613d20

PlanningNodeClass *PlanningTokenClass::Loop_Node()
{
    if (LoopStart == -1) {
        return 0;
    }
    return Nodes[LoopStart];
}
