// bool XSurface::Draw_Depth_Antialiased_Line(Rect const &, Point2D const &, Point2D const &,
// RGBClass const &, int, int, bool, bool, bool, bool, float) (0x00773EE0, slot 15)
// Not implemented by the generic surface: returns false (DSurface overrides it, 0x004AC650).
// Name and parameter list from TibSun's XSurface (11 stack arguments, ret 0x2c).
#include "shared/surface.hpp"

bool XSurface::Draw_Depth_Antialiased_Line(Rect const &, Point2D const &, Point2D const &, RGBClass const &, int,
                                           int, bool, bool, bool, bool, float)
{
    return false;
}
