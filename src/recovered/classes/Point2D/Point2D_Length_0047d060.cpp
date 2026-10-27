// Integer vector length through the original table square root.
#include "shared/rect.hpp"
#include "shared/fast_math.hpp"
// @ref ?Fast_Sqrt@@YAMN@Z=004ba410
int Point2D::Length() const
{
    return (int)Fast_Sqrt((double)X * X + (double)Y * Y);
}
