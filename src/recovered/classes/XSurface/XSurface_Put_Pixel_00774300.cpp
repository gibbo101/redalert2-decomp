// bool XSurface::Put_Pixel(Point2D const &point, int color, Rect const &cliprect) (0x00774300, slot 34)
// Stores one pixel when the point lies inside cliprect.
// The point goes to Lock by value (Lock takes a Point2D).
#include "shared/surface.hpp"

bool XSurface::Put_Pixel(Point2D const &point, int color, Rect const &cliprect)
{
    if (cliprect.Is_Point_Within(point)) {
        void *pixel = Lock(point);
        if (pixel != 0) {
            if (Bytes_Per_Pixel() == 2) {
                *(unsigned short *)pixel = (unsigned short)color;
            } else {
                *(unsigned char *)pixel = (unsigned char)color;
            }
            Unlock();
            return true;
        }
    }
    return false;
}
