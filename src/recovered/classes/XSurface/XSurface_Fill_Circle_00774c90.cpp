// void XSurface::Fill_Circle (0x00774C90; TibSun xsurface.cpp Draw_Circle): fills the
// circle with horizontal clipped lines, stepping the midpoint circle algorithm
// through one octant and mirroring it.
#include "shared/surface.hpp"

void XSurface::Fill_Circle(Point2D center, int radius, Rect cliprect, int color)
{
    Point2D pt(radius, 0);
    const int roundness_val = 2;
    int d = 3 - (roundness_val * radius);
    do {
        Draw_Line(cliprect, center + Point2D(-pt.X, pt.Y), center + Point2D(pt.X, pt.Y), color);
        Draw_Line(cliprect, center + Point2D(-pt.Y, pt.X), center + Point2D(pt.Y, pt.X), color);
        Draw_Line(cliprect, center + Point2D(-pt.X, -pt.Y), center + Point2D(pt.X, -pt.Y), color);
        Draw_Line(cliprect, center + Point2D(-pt.Y, -pt.X), center + Point2D(pt.Y, -pt.X), color);
        if (d < 0) {
            d += (4 * pt.Y) + 6;
        } else {
            d += 4 * (pt.Y - pt.X) + 10;
            pt.X--;
        }
        pt.Y++;
    } while (pt.X >= pt.Y);
}
