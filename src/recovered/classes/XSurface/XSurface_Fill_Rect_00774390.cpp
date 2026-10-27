// bool XSurface::Fill_Rect(Rect const &fillrect, int color) (0x00774390, slot 5)
// Fills fillrect: passes it as the clip rectangle and the whole surface
// rectangle (placed relative to it) as the area, so exactly fillrect,
// clipped to the surface, is filled.
#include "shared/surface.hpp"
// @ref ?Fill_Rect@XSurface@@UAE_NABVRect@@0H@Z=007743c0

bool XSurface::Fill_Rect(Rect const &fillrect, int color)
{
    return XSurface::Fill_Rect(fillrect, Get_Rect(), color);
}
