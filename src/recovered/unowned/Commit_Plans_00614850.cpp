// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright 2026 ra2-decomp contributors
// Copyright 2025 Electronic Arts Inc.; 2026 OpenTS contributors
// Derived from Electronic Arts source code; EA's GPL Section 7 terms apply (COPYING.md).
#define RA2_COORD_EQUAL_MEMBER
// void __fastcall Commit_Plans(int house) (0x00614850)
// Adopted from ra2-decomp Commit_Plans (YR 0x00637AB0).
// For every planning techno of a house: clears its path's loop marks, and
// when its path was not under way but its mission allows it, starts the
// path again. Planning_Execute (0x00614BA0) expands it inline for event 0x2B.
#include "shared/planning.hpp"
// @ref ?Planning_House@@YIHPAVTechnoClass@@@Z=00610770
// @ref ?unknown_613310@PlanningTokenClass@@QBE_NXZ=00613310
// @ref ?Commit_Plans@@YIXH@Z=00614850

static inline void Commit_Unit_Orders(TechnoClass *techno)
{
    PlanningTokenClass *token = Planning_Token(techno);
    if (token != 0) {
        bool started = token->unknown_613310();
        token->unknown_613a80();
        bool permitted = Planning_Mission_Allows(techno);
        if (!started && permitted) {
            techno->unknown_615360();
        }
    }
}

void __fastcall Commit_Plans(int house)
{
    int count = unknown_list_a40c20.Count();
    for (int i = 0; i < count; i++) {
        TechnoClass *techno = unknown_list_a40c20[i];
        if (house == Planning_House(techno)) {
            Commit_Unit_Orders(techno);
        }
    }
}
