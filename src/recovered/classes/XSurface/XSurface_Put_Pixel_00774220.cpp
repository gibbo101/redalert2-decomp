// bool XSurface::Put_Pixel(Point2D const &point, int color) (0x00774220, slot 9)
// Stores one pixel (1 or 2 bytes); false when the surface cannot be locked.
#include "shared/surface.hpp"

bool XSurface::Put_Pixel(Point2D const &point, int color)
{
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
    return false;
}
