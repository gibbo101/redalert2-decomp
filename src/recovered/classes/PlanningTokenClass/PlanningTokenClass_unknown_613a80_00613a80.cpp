// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright 2026 ra2-decomp contributors
// Copyright 2025 Electronic Arts Inc.; 2026 OpenTS contributors
// Derived from Electronic Arts source code; EA's GPL Section 7 terms apply (COPYING.md).
#define RA2_COORD_EQUAL_MEMBER
// void PlanningTokenClass::unknown_613a80() (0x00613A80)
// Clears the loop marks of the loop start (once) and of every node from the
// first one on. Statement shape from ra2-decomp PlanningTokenClass::FUN_00636CE0
// (YR 0x00636CE0).
#include "shared/planning.hpp"

void PlanningTokenClass::unknown_613a80()
{
    if (unknown_98) {
        PlanningNodeClass *node = Loop_Node();
        if (node != 0) node->unknown_612b50(true);
        unknown_98 = false;
    }
    int start = unknown_8c == -1 ? 0 : unknown_8c;
    int count = Nodes.Count();
    for (int index = start; index < count; index++) {
        PlanningNodeClass *node = Nodes[index];
        if (node != 0) node->unknown_612b50(true);
    }
    unknown_8c = -1;
}
