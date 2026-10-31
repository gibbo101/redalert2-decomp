// void Tactical::AI() -- 0x006A2DD0 (slot 23)
// Purpose: each new frame, advances the scroll animation from unknown_c8 to
// unknown_d0 (unknown_dc is the progress, unknown_d8 the step), moves the
// view position through the clamp 0x006A8C80, restarts the update-count timer
// at Rules->WaypointAnimationSpeed once it ran out, and applies a requested
// view position (unknown_d74) when the animation did not move it.
// Assumptions: unknown_a40d04 / unknown_a40d13 are game flags of unknown
// meaning; the comparison with 0x00ABE540 is by value.
#include "shared/tactical.hpp"
#include "shared/rules.hpp"
#include "shared/unknown_globals.hpp"
// @ref ?Unknown_006A8C80@Tactical@@QAE_NPAUPoint2D@@@Z=006a8c80
// @ref ?Unknown_006A9170@Tactical@@QAEXXZ=006a9170
// @ref ?Lerp@@YI?AUPoint2D@@ABU1@0M@Z=00722140
// @ref ?unknown_abe540@@3UPoint2D@@A=00abe540/00abe544

extern Point2D unknown_abe540;    // 0x00ABE540 (the header static unknown_geometry_l, read as a point)
Point2D __fastcall Lerp(Point2D const &from, Point2D const &to, float t);

void Tactical::AI()
{
    bool moved = false;
    if (unknown_flags_a3f600 & 2) {
        return;
    }
    if (unknown_a8 != Frame) {
        if (unknown_flag_a40d04 && unknown_d0 != unknown_abe540 && unknown_d8 != 0.0f) {
            unknown_dc = unknown_dc + unknown_d8;
            if (unknown_dc > 1.0) {
                unknown_dc = 1.0f;
            }
            Point2D pos = Lerp(unknown_c8, unknown_d0, unknown_dc);
            if (unknown_dc >= 1.0) {
                unknown_d0 = Point2D(0, 0);
                unknown_c8 = Point2D(0, 0);
                unknown_d8 = 0;
                unknown_dc = 0;
            }
            Point2D point = pos;
            int x;
            int y;
            if (Unknown_006A8C80(&point) && !unknown_a40d13) {
                x = point.X;
                y = point.Y;
            } else {
                x = pos.X;
                y = pos.Y;
            }
            unknown_d64 = Point2D(x, y);
            unknown_d74 = Point2D(x, y);
            Unknown_006A9170();
            unknown_d7d = true;
            moved = true;
        }
        if (unknown_da4.Value() == 0) {
            unknown_da4 = CDTimerClass<SystemTimerClass>(Rules->WaypointAnimationSpeed);
            unknown_da0++;
        }
    }
    unknown_a8 = Frame;
    if (unknown_d74 != unknown_d64 && !moved) {
        Point2D point = unknown_d74;
        int x;
        int y;
        if (Unknown_006A8C80(&point) && !unknown_a40d13) {
            x = point.X;
            y = point.Y;
        } else {
            x = unknown_d74.X;
            y = unknown_d74.Y;
        }
        unknown_d64 = Point2D(x, y);
        unknown_d74 = Point2D(x, y);
        Unknown_006A9170();
        unknown_d7d = true;
    }
}
