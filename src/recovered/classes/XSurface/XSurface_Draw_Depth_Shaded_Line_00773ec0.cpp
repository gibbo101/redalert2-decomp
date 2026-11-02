// bool XSurface::Draw_Depth_Shaded_Line(Rect const &, Point2D const &, Point2D const &, unsigned,
// int, int, bool) (0x00773EC0, slot 13)
// Not implemented by the generic surface: returns false (DSurface overrides it, 0x004AFC30).
// Name and parameter list from TibSun's XSurface (7 stack arguments, ret 0x1c).
#include "shared/surface.hpp"

bool XSurface::Draw_Depth_Shaded_Line(Rect const &, Point2D const &, Point2D const &, unsigned, int, int, bool)
{
    return false;
}
