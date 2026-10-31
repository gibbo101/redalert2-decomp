// Point2D __fastcall Lerp(Point2D const &from, Point2D const &to, float t) (0x00722140)
// The screen point a fraction t of the way from from to to (TibSun Lerp).
#include "shared/wave.hpp"

Point2D __fastcall Lerp(Point2D const &from, Point2D const &to, float t)
{
    return Point2D((int)(to.X * t + from.X * (1.0 - t)), (int)(to.Y * t + from.Y * (1.0 - t)));
}
