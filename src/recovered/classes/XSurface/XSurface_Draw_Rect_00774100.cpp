// bool XSurface::Draw_Rect(Rect const &rect, int color) (0x00774100, slot 22)
// Outlines rect clipped to the whole surface.
#include "shared/surface.hpp"
// @ref ?Draw_Rect@XSurface@@UAE_NABVRect@@0H@Z=00774130

bool XSurface::Draw_Rect(Rect const &rect, int color)
{
    return XSurface::Draw_Rect(Get_Rect(), rect, color);
}
