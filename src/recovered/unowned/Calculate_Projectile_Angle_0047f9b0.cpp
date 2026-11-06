// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright 2026 ra2-decomp contributors
// Copyright 2025 Electronic Arts Inc.; 2026 OpenTS contributors
// Derived from Electronic Arts source code; EA's GPL Section 7 terms apply (COPYING.md).
// bool __fastcall Calculate_Projectile_Angle(bool high_arc, int speed, int distance, int height, double gravity, double &angle) -- 0x0047F9B0
// Adopted from ra2-decomp Calculate_Projectile_Angle (YR 0x0048A9D0).
// The launch angle (radians) reaching distance and height at speed under
// gravity, on the high or the low arc; a target above the shooter takes a
// fixed 45 degrees. False when no arc reaches it.
#include "shared/fast_math.hpp"
#include "shared/combat.hpp"

bool __fastcall Calculate_Projectile_Angle(bool high_arc, int speed, int distance, int height, double gravity, double &angle)
{
    if (height > 0) {
        angle = 0.7853822499999998;
        return true;
    }

    if ((double)distance == 0.0) {
        distance = 0;
    }

    double dx = (double)distance;
    double velocity = (double)speed;
    double dy = (double)height;
    double v = velocity;

    double vsq = v * v;
    double base = vsq - ((double)height * gravity);
    double g2 = gravity * gravity;
    double dx2 = (dx * dx);

    double value = (v * v * vsq)
                 - (2 * vsq * dy * gravity)
                 - (g2 * dx2);

    double denominator = (((dy * dy) / dx2) + 1.0) * 2;

    if (value < 0.0 || denominator == 0.0) {
        return false;
    }

    double numerator = !high_arc ? base + Fast_Sqrt(value)
                                 : base - Fast_Sqrt(value);

    value = numerator / denominator;

    if (value >= 0.0) {
        angle = Fast_Asin(Fast_Sqrt(value) / v);    // ra2-decomp fastmath::acos: 0x004BA580 (our Fast_Asin is pi/2 less the 0x004BA550 table, i.e. the arc cosine; the two names look swapped)
        return true;
    }
    return false;
}
