// bool XSurface::Unknown_Slot16(Rect const &, Point2D const &, Point2D const &, RGBClass const &, float,
// int, int) (0x00773EF0, slot 16)
// Not implemented by the generic surface: returns false. DSurface's 0x004ADE00 reads the colour's
// three bytes and scales them by the float; LaserDrawClass::Draw_It 0x005334F0 passes the depths last.
#include "shared/surface.hpp"

bool XSurface::Unknown_Slot16(Rect const &, Point2D const &, Point2D const &, RGBClass const &, float, int, int)
{
    return false;
}
