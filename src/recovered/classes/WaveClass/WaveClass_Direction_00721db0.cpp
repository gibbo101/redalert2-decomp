#include "shared/wave.hpp"
#include "shared/fast_math.hpp"
int __fastcall Wave_Direction_00721db0(Point2D const &start, Point2D const &end)
{
    int dx = end.X - start.X;
    int dy = start.Y - end.Y;
    double sine = Fast_Sin(0.39269908169872414);
    double tangent = sine / Fast_Cos(0.39269908169872414);
    if (dx != 0) {
        double slope = (double)dy / dx;
        if (slope < 1.0 / tangent && slope >= tangent) return dx > 0 ? 1 : 5;
        if (slope < tangent && slope >= -tangent) return dx > 0 ? 2 : 6;
        if (slope < -tangent && slope >= -1.0 / tangent) return dx > 0 ? 3 : 7;
    }
    return dy > 0 ? 0 : 4;
}
