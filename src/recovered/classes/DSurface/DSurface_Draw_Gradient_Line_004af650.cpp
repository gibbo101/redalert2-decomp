// Draw a clipped 16-bit line whose colour moves between two palette colours:
// every pixel takes the colour at ratio between from and to, and ratio
// advances by step, bouncing between 0 and 1.
#include "shared/crt_memory.hpp"
#include "shared/dsurface.hpp"
#include "shared/hicolor.hpp"
#include "shared/rgb_class.hpp"
// @ref ?Clip_Line@@YI_NAAUPoint2D@@0ABVRect@@@Z=00775620
// @ref ?Intersect@@YI?AVRect@@ABV1@0PAH1@Z=0041fdf0
// @ref ??0RGBClass@@QAE@ABV0@0M@Z=0063cc80

// The screen pixel of the colour at ratio between from and to.
inline unsigned short Gradient_Pixel(RGBClass const &from, RGBClass const &to, float const &ratio)
{
    RGBClass color = RGBClass(from, to, ratio);
    return (unsigned short)(((unsigned short)(unsigned char)(color.Red >> unknown_shift_852fbc) << unknown_shift_852fb8)
         | ((unsigned short)(unsigned char)(color.Green >> unknown_shift_852fcc) << unknown_shift_852fc8)
         | ((unsigned short)(unsigned char)(color.Blue >> unknown_shift_852fc4) << unknown_shift_852fc0));
}

// Advance ratio by step, reversing at 0 and 1.
inline void Step_Ratio(float &ratio, float &step)
{
    ratio += step;
    if (ratio < 0.0f && step < 0.0f) {
        ratio = 0.0f;
        step = -step;
    } else if (ratio > 1.0f && step > 0.0f) {
        ratio = 1.0f;
        step = -step;
    }
}

bool DSurface::Draw_Gradient_Line(Rect const &cliprect, Point2D const &startpoint, Point2D const &endpoint,
                                  RGBClass const &from, RGBClass const &to, float &step, float &ratio)
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
        if (Bytes_Per_Pixel() == 2) {
            unsigned short *pixels = (unsigned short *)Lock(start);
            if (pixels) {
                if (start.Y == end.Y) {
                    for (int index = 0; index <= end.X - start.X; ++index) {
                        pixels[index] = Gradient_Pixel(from, to, ratio);
                        Step_Ratio(ratio, step);
                    }
                } else if (start.X == end.X) {
                    int stride;
                    if (start.Y > end.Y) stride = -Stride();
                    else stride = Stride();
                    int height = abs(end.Y - start.Y);
                    for (int index = 0; index <= height; ++index) {
                        *pixels = Gradient_Pixel(from, to, ratio);
                        Step_Ratio(ratio, step);
                        pixels = (unsigned short *)((char *)pixels + stride);
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
                        for (int index = 0; index <= dx; ++index) {
                            pixels[index] = Gradient_Pixel(from, to, ratio);
                            Step_Ratio(ratio, step);
                            if (error > 0) {
                                pixels = (unsigned short *)((char *)pixels + stride);
                                error -= dx2;
                            }
                            error += dy2;
                        }
                    } else {
                        int error = dx2 - dy;
                        int offset = 0;
                        for (int count = 0; count <= dy; ++count) {
                            pixels[offset] = Gradient_Pixel(from, to, ratio);
                            Step_Ratio(ratio, step);
                            if (error > 0) {
                                ++offset;
                                error -= dy2;
                            }
                            error += dx2;
                            pixels = (unsigned short *)((char *)pixels + stride);
                        }
                    }
                }
                Unlock();
                return true;
            }
        }
    }
    return false;
}
