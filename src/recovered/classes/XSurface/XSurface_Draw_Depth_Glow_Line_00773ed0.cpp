// bool XSurface::Draw_Depth_Glow_Line(Rect const &, Point2D const &, Point2D const &,
//     int, int, int, bool) (0x00773ED0, slot 14)
// Not implemented by the generic surface: returns false. The signature is
// TibSun's (dsurface.h Draw_Depth_Glow_Line; 7 stack arguments, ret 0x1c);
// DSurface overrides it (0x004ABBA0).
#include "shared/surface.hpp"

bool XSurface::Draw_Depth_Glow_Line(Rect const &, Point2D const &, Point2D const &, int, int, int, bool)
{
    return false;
}
