// bool DSurface::Fill_Rect(Rect const &fillrect, int color) (0x004AB4F0, slot 5)
// Fills fillrect clipped to the whole surface.
#include "shared/dsurface.hpp"
// @ref ?Fill_Rect@DSurface@@UAE_NABVRect@@0H@Z=004ab520

bool DSurface::Fill_Rect(Rect const &fillrect, int color)
{
    return DSurface::Fill_Rect(Get_Rect(), fillrect, color);
}
