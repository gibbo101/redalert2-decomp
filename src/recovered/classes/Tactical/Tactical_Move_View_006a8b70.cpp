// void Tactical::Unknown_006A8B70(int direction, int distance) (0x006A8B70)
// Moves the view position along one of eight facing directions (table of Point2D unit steps, a function-local
// static) and carries the requested position by the same delta.
// @ref _?$S1@?1??Unknown_006A8B70@Tactical@@QAEXHH@Z@4EA=00abe5d0
// @ref _?directions@?1??Unknown_006A8B70@Tactical@@QAEXHH@Z@4PAUPoint2D@@A=00abe570
#include "shared/tactical.hpp"
#include "shared/unknown_globals.hpp"

void Tactical::Unknown_006A8B70(int arg1, int arg2)
{
    static Point2D directions[8] = {
        Point2D(0, -1), Point2D(1, -1), Point2D(1, 0), Point2D(1, 1),
        Point2D(0, 1), Point2D(-1, 1), Point2D(-1, 0), Point2D(-1, -1)
    };
    int x = unknown_d64.X;
    int y = unknown_d64.Y;
    int newx = directions[arg1].X * arg2 + x;
    int newy = directions[arg1].Y * arg2 + y;
    if (x != newx || y != newy) {
        Point2D d(newx - x, newy - y);
        unknown_d74.X += d.X;
        unknown_d74.Y += d.Y;
    }
}
