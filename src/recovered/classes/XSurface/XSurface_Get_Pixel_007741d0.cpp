// int XSurface::Get_Pixel(Point2D const &point) (0x007741D0, slot 10)
// Reads one pixel (1 or 2 bytes); 0 when the surface cannot be locked.
#include "shared/surface.hpp"

int XSurface::Get_Pixel(Point2D const &point)
{
    int color = 0;
    void *pixel = Lock(point);
    if (pixel != 0) {
        if (Bytes_Per_Pixel() == 2) {
            color = *(unsigned short *)pixel;
        } else {
            color = *(unsigned char *)pixel;
        }
        Unlock();
    }
    return color;
}
