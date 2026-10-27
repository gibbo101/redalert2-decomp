// Draw the 16-entry dash pattern along a line and return its updated phase.
#include "shared/surface.hpp"
#include "shared/crt_memory.hpp"
int XSurface::Draw_Dashed_Line(Point2D const &startpoint, Point2D const &endpoint, int color,
bool const *pattern, int phase)
{
    Point2D start = startpoint;
    Point2D end = endpoint;
    int step = 1;
    if (start.X > end.X) {
        Point2D temp = start;
        start = end;
        end = temp;
        int length = abs(start.X - end.X);
        int height = abs(start.Y - end.Y) + 1;
        if (length < height) length = height;
        phase = (phase + length) % 16;
        step = -1;
    }
    int bytes_per_pixel = Bytes_Per_Pixel();
    unsigned char *pixels = (unsigned char *)Lock(start);
    if (pixels) {
        unsigned char color8 = (unsigned char)color;
        unsigned short color16 = (unsigned short)color;
        if (start.Y == end.Y) {
            // The original horizontal path writes 16-bit pixels unconditionally.
            int width = end.X - start.X;
            for (int index = 0; index <= width; ++index) {
                if (phase < 0) phase += 16;
                if (phase >= 16) phase -= 16;
                if (pattern[phase]) *(unsigned short *)pixels = color16;
                pixels += 2;
                phase += step;
            }
        } else if (start.X == end.X) {
            int stride;
            if (start.Y > end.Y) stride = -Stride();
            else stride = Stride();
            int height = abs(end.Y - start.Y);
            for (int index = 0; index <= height; ++index) {
                if (phase < 0) phase += 16;
                if (phase >= 16) phase -= 16;
                if (pattern[phase]) {
                    if (bytes_per_pixel == 1) *pixels = color8;
                    else *(unsigned short *)pixels = color16;
                }
                pixels += stride;
                phase += step;
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
                for (int index = 0; index < dx; phase += step) {
                    if (phase < 0) phase += 16;
                    if (phase >= 16) phase -= 16;
                    if (pattern[phase]) {
                        if (bytes_per_pixel == 1) pixels[index] = color8;
                        else ((unsigned short *)pixels)[index] = color16;
                    }
                    if (error > 0) {
                        pixels += stride;
                        error -= dx2;
                    }
                    error += dy2;
                    ++index;
                }
            } else {
                int error = dx2 - dy;
                int offset = 0;
                for (int count = dy; count > 0; --count) {
                    if (phase < 0) phase += 16;
                    if (phase >= 16) phase -= 16;
                    if (pattern[phase]) {
                        if (bytes_per_pixel == 1) pixels[offset] = color8;
                        else ((unsigned short *)pixels)[offset] = color16;
                    }
                    if (error > 0) {
                        ++offset;
                        error -= dy2;
                    }
                    error += dx2;
                    pixels += stride;
                    phase += step;
                }
            }
        }
        Unlock();
    }
    return phase;
}
