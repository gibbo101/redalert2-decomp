// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright 2026 ra2-decomp contributors
// Copyright 2025 Electronic Arts Inc.; 2026 OpenTS contributors
// Derived from Electronic Arts source code; EA's GPL Section 7 terms apply (COPYING.md).
// Point2D __fastcall Rectangular_To_Isometric(Point2D point) (0x006A2740): a rectangular point rotated onto
// the isometric axes (TibSun Tactical::Rectangular_To_Isometric; written as ra2-decomp's
// Tactical::Rectangular_To_Isometric, YR 0x006D1EB0, the same arithmetic as 0x006A6800). The hidden result
// comes in ecx and the point on the stack, which is why the old TacticalProjection constructor spelling also fit.
#include "shared/tactical.hpp"

Point2D __fastcall Rectangular_To_Isometric(Point2D point)
{
    Point2D iso;
    iso.X = point.X * 60 / 2;
    iso.Y = point.X * 30 / 2;
    iso.X += point.Y * 60 / -2;
    iso.Y += point.Y * 30 / 2;
    return iso;
}
