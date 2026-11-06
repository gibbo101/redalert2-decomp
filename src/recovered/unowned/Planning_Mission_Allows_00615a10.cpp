// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright 2026 ra2-decomp contributors
// Copyright 2025 Electronic Arts Inc.; 2026 OpenTS contributors
// Derived from Electronic Arts source code; EA's GPL Section 7 terms apply (COPYING.md).
#define RA2_COORD_EQUAL_MEMBER
// bool __fastcall Planning_Mission_Allows(TechnoClass *techno) (0x00615A10)
// Whether the techno's current mission lets planning mode take over: mission
// 5, or mission 1 / 0xB whose target is a building (kind 0xB) or, for 0xB,
// absent. Statement shape from ra2-decomp FUN_00638C70 (YR 0x00638C70).
#include "shared/planning.hpp"

static inline bool Mission_Fits(int mission, TargetClass target)
{
    if (mission == 1 || mission == 0x0B) {
        if (target.Kind == 0x0B) goto fits;
        if (mission == 0x0B && target.Kind == 0) {
fits:
            return true;
        }
    }
    return false;
}

bool __fastcall Planning_Mission_Allows(TechnoClass *techno)
{
    if (techno) {
        int mission = techno->unknown_slot91();
        if (mission == 5) {
            return true;
        }
        return Mission_Fits(mission, TargetClass(techno->unknown_228));
    }
    return false;
}
