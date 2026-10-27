// Clip a line, lock at its first endpoint, and write its pixels in the surface format.
#include "shared/surface.hpp"
#include "shared/crt_memory.hpp"
// @ref ?Clip_Line@@YI_NAAUPoint2D@@0ABVRect@@@Z=00775620
// @ref ?Intersect@@YI?AVRect@@ABV1@0PAH1@Z=0041fdf0
bool XSurface::Draw_Line(Rect const &cliprect, Point2D const &startpoint, Point2D const &endpoint, int color)
{
    Rect clip = cliprect.Intersect(Get_Rect());
    Point2D start = Offset_Point(startpoint, clip);
    Point2D end = Offset_Point(endpoint, clip);
    if (Clip_Line(start, end, clip)) {
        if (start.X > end.X) {
            Point2D temp = start;
            start = end;
            end = temp;
        }
        int bytes_per_pixel = Bytes_Per_Pixel();
        unsigned char *pixels = (unsigned char *)Lock(start);
        if (pixels) {
            unsigned char color8 = (unsigned char)color;
            unsigned short color16 = (unsigned short)color;
            if (start.Y == end.Y) {
                if (bytes_per_pixel == 1) {
                    memset(pixels, color, end.X - start.X + 1);
                } else {
                    for (int index = 0; index <= end.X - start.X; pixels += 2) {
                        *(unsigned short *)pixels = color16;
                        ++index;
                    }
                }
            } else if (start.X == end.X) {
                int stride;
                if (start.Y > end.Y) stride = -Stride();
                else stride = Stride();
                int height = abs(end.Y - start.Y);
                for (int index = 0; index <= height; ++index) {
                    if (bytes_per_pixel == 1) *pixels = color8;
                    else *(unsigned short *)pixels = color16;
                    pixels += stride;
                }
            } else {
                int dx = end.X - start.X;
                int dy = end.Y - start.Y;
                int stride = Stride();
                if (dy < 0) stride = -stride;
                dy = abs(dy);
                int dx2 = dx * 2;
                int dy2 = dy * 2;
                if (dx > dy) {
                    int error = dy2 - dx;
                    for (int index = 0; index < dx; ++index) {
                        if (bytes_per_pixel == 1) pixels[index] = color8;
                        else ((unsigned short *)pixels)[index] = color16;
                        if (error > 0) {
                            pixels += stride;
                            error -= dx2;
                        }
                        error += dy2;
                    }
                } else {
                    int error = dx2 - dy;
                    int offset = 0;
                    for (int count = dy; count > 0; --count) {
                        if (bytes_per_pixel == 1) pixels[offset] = color8;
                        else ((unsigned short *)pixels)[offset] = color16;
                        if (error > 0) {
                            ++offset;
                            error -= dy2;
                        }
                        error += dx2;
                        pixels += stride;
                    }
                }
            }
            Unlock();
            return true;
        }
    }
    return false;
}
