// Point2D *__fastcall Unknown_00722140(Point2D *result, Point2D const &b, Point2D const &a, float amount) (0x00722140)
// The two-dimensional version of Unknown_007220C0.
#include "shared/wave.hpp"

Point2D *__fastcall Unknown_00722140(Point2D *result, Point2D const &b, Point2D const &a, float amount)
{
    *result = Point2D((int)(a.X * amount + b.X * (1.0 - amount)), (int)(a.Y * amount + b.Y * (1.0 - amount)));
    return result;
}
