// bool XSurface::Draw_Line(Point2D const &startpoint, Point2D const &endpoint, int color) (0x00773950, slot 12)
// Draws a line clipped to the whole surface.
#include "shared/surface.hpp"
// @ref ?Draw_Line@XSurface@@UAE_NABVRect@@ABUPoint2D@@1H@Z=00773980

bool XSurface::Draw_Line(Point2D const &startpoint, Point2D const &endpoint, int color)
{
    return XSurface::Draw_Line(Get_Rect(), startpoint, endpoint, color);
}
