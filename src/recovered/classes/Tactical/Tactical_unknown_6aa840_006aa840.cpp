// int Tactical::Unknown_006AA840(int direction) (0x006AA840): moves the view position one step in a
// facing direction (function-local static table, atexit stub 0x006AA960), clamped by 0x006A8C80 unless
// 0x00A40D13 is set; returns the facing of the step actually taken (3x3 table 0x007F6930), or the
// direction when the step is empty.
// @ref _?$S1@?1??Unknown_006AA840@Tactical@@QAEHH@Z@4EA=00abe4bc
// @ref _?directions@?1??Unknown_006AA840@Tactical@@QAEHH@Z@4PAUPoint2D@@A=00abe4e0
// @ref ?unknown_facings_7f6930@@3PAY02HA=007f6930
#include "shared/tactical.hpp"
#include "shared/unknown_globals.hpp"

extern int unknown_facings_7f6930[3][3];

int Tactical::Unknown_006AA840(int direction)
{
    static Point2D directions[8] = {
        Point2D(0, -1), Point2D(1, -1), Point2D(1, 0), Point2D(1, 1),
        Point2D(0, 1), Point2D(-1, 1), Point2D(-1, 0), Point2D(-1, -1)
    };
    int x = unknown_d64.X;
    int y = unknown_d64.Y;
    int newx = directions[direction].X + x;
    int newy = directions[direction].Y + y;
    if (newx != x || newy != y) {
        Point2D point(newx, newy);
        if (Unknown_006A8C80(&point) && !unknown_a40d13) {
            newx = point.X;
            newy = point.Y;
        }
        Point2D delta(unknown_d64.X - newx, unknown_d64.Y - newy);
        return unknown_facings_7f6930[delta.Y + 1][delta.X + 1];
    }
    return direction;
}
