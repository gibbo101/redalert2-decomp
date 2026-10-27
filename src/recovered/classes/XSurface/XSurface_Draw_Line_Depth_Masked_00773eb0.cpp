// bool XSurface::Draw_Line_Depth_Masked(...) (0x00773EB0, slot 20)
// The generic surface has no depth buffer: draws nothing and returns false
// (DSurface 0x004B0D30 implements it for 16-bit surfaces).
#include "shared/surface.hpp"

bool XSurface::Draw_Line_Depth_Masked(Point2D const &, Point2D const &, int, bool)
{
    return false;
}
