// int XSurface::Draw_Dashed_Line_Depth_Masked(...) (0x00773EA0, slot 19)
// The generic surface has no depth buffer: draws nothing and returns 0
// (DSurface 0x004B0650 implements it for 16-bit surfaces).
#include "shared/surface.hpp"

int XSurface::Draw_Dashed_Line_Depth_Masked(Point2D const &, Point2D const &, int, bool const *, int, bool)
{
    return 0;
}
