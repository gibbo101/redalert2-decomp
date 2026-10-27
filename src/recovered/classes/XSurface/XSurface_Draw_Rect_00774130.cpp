// bool XSurface::Draw_Rect(Rect const &cliprect, Rect const &rect, int color) (0x00774130, slot 21)
// Outlines rect (inclusive corners) with four clipped Draw_Line calls.
#include "shared/surface.hpp"

bool XSurface::Draw_Rect(Rect const &cliprect, Rect const &rect, int color)
{
    Point2D topleft;
    Point2D topright;
    Point2D bottomright;
    Point2D bottomleft;
    topleft.X = rect.X;
    topleft.Y = rect.Y;
    topright.X = rect.X + rect.Width - 1;
    topright.Y = rect.Y;
    bottomleft.X = rect.X;
    bottomleft.Y = rect.Y + rect.Height - 1;
    bottomright.X = rect.X + rect.Width - 1;
    bottomright.Y = rect.Y + rect.Height - 1;

    Draw_Line(cliprect, topleft, topright, color);
    Draw_Line(cliprect, topleft, bottomleft, color);
    Draw_Line(cliprect, topright, bottomright, color);
    Draw_Line(cliprect, bottomleft, bottomright, color);
    return true;
}
