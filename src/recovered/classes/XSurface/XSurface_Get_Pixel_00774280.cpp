// int XSurface::Get_Pixel(Point2D const &point, Rect const &cliprect) (0x00774280, slot 35)
// Reads one pixel when the point lies inside cliprect; 0 otherwise.
// The point goes to Lock by value (Lock takes a Point2D).
#include "shared/surface.hpp"

int XSurface::Get_Pixel(Point2D const &point, Rect const &cliprect)
{
    int color = 0;
    if (cliprect.Is_Point_Within(point)) {
        void *pixel = Lock(point);
        if (pixel != 0) {
            if (Bytes_Per_Pixel() == 2) {
                color = *(unsigned short *)pixel;
            } else {
                color = *(unsigned char *)pixel;
            }
            Unlock();
        }
    }
    return color;
}
