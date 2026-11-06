// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright 2026 ra2-decomp contributors
// Copyright 2025 Electronic Arts Inc.; 2026 OpenTS contributors
// Derived from Electronic Arts source code; EA's GPL Section 7 terms apply (COPYING.md).
#define RA2_COORD_EQUAL_MEMBER
// bool PlanningTokenClass::unknown_613310() const (0x00613310)
// Adopted from ra2-decomp PlanningTokenClass::Has_Started (YR 0x00636570).
// Whether the path has nodes and its first-node index is -1 or above 0.
#include "shared/planning.hpp"
// @ref ?unknown_613310@PlanningTokenClass@@QBE_NXZ=00613310

bool PlanningTokenClass::unknown_613310() const
{
    return Nodes.Count() > 0 && (unknown_8c == -1 || unknown_8c > 0);
}
