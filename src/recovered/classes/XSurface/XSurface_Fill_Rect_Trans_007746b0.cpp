// bool XSurface::Fill_Rect_Trans(Rect const &rect, RGBClass const &color, unsigned int percent)
// (0x007746B0, slot 7)
// Not implemented by the generic surface: returns false (DSurface blends,
// 0x004AB730).
#include "shared/surface.hpp"

bool XSurface::Fill_Rect_Trans(Rect const &, RGBClass const &, unsigned int)
{
    return false;
}
