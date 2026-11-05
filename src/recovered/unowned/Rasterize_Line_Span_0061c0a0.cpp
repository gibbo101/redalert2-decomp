// Rasterize one polygon edge into successive left or right scanline bounds,0061C0A0.
#include "shared/rect.hpp"
extern "C" int __cdecl abs(int);

void __fastcall Rasterize_Line_Span_0061c0a0(int x, int y, int end_x, int end_y, int side, int skip, Point2D *&cursor)
{
    Point2D *out = cursor;
    int direction = end_x - x > 0 ? 1 : -1;
    int dx = end_x - x;
    int dy = end_y - y;
    if (dy > 0) {
        int width = abs(dx);
        if (width == 0) {
            int rows = dy - skip;
            while (rows-- > 0) {
                if (side == 1) out->X = x;
                else out->Y = x;
                ++out;
            }
        } else if (dy == width) {
            if (skip) x += direction;
            int rows = dy - skip;
            while (rows-- > 0) {
                if (side == 1) out->X = x;
                else out->Y = x;
                x += direction;
                ++out;
            }
        } else if (dy > width) {
            int error = dx >= 0 ? 0 : 1 - dy;
            if (skip) {
                error += width;
                if (error > 0) {
                    x += direction;
                    error -= dy;
                }
            }
            int rows = dy - skip;
            while (rows-- > 0) {
                if (side == 1) out->X = x;
                else out->Y = x;
                error += width;
                if (error > 0) {
                    x += direction;
                    error -= dy;
                }
                ++out;
            }
        } else {
            int step = width / dy * direction;
            int remainder = width % dy;
            int error = dx >= 0 ? 0 : 1 - dy;
            if (skip) {
                error += remainder;
                x += step;
                if (error > 0) {
                    x += direction;
                    error -= dy;
                }
            }
            int rows = dy - skip;
            while (rows-- > 0) {
                if (side == 1) out->X = x;
                else out->Y = x;
                error += remainder;
                x += step;
                if (error > 0) {
                    x += direction;
                    error -= dy;
                }
                ++out;
            }
        }
        cursor = out;
    }
}
