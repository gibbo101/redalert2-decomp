// Copy an area-sized block of alpha values, starting at the ring's current
// origin, into surface at the area's position (a view of the buffer).
#include "shared/blit.hpp"
void ABuffer::Copy_To(::Surface &surface, Rect area)
{
    unsigned short *pixels = (unsigned short *)surface.Lock(Point2D(area.X, area.Y));
    unsigned short *alpha = (unsigned short *)(BufferHead + BufferOffset);
    int skip = surface.Stride() / 2 - area.Width;
    if (pixels && area.Height > 0) {
        for (int row = area.Height; row; --row) {
            for (int column = area.Width; column > 0; --column) {
                *pixels++ = *alpha++;
                alpha = Wrap_Pointer(alpha);
            }
            pixels += skip;
        }
    }
    surface.Unlock();
}
