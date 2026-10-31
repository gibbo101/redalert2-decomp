// bool DSurface::Fill_Rect_Trans(Rect const &rect, RGBClass const &color, unsigned int percent)
// (0x004AB730, slot 7)
// Blends color over the part of rect on the surface, percent (at most 100)
// of the way: each channel becomes (background * (255 - a) + color * a) / 256
// with a = percent * 255 / 100, kept to its bits of the screen pixel format.
// 16-bit surfaces only.
#include "shared/dsurface.hpp"
#include "shared/hicolor.hpp"
#include "shared/rgb_class.hpp"
// @ref ?Top_Left@Rect@@QBE?AURectPoint2D@@XZ=00435560
// @ref ?Intersect@@YI?AVRect@@ABV1@0PAH1@Z=0041fdf0

bool DSurface::Fill_Rect_Trans(Rect const &rect, RGBClass const &color, unsigned int percent)
{
    if (Bytes_Per_Pixel() < 2) return false;
    if (!rect.Is_Valid()) return false;
    Rect area = Get_Rect().Intersect(rect);
    if (!area.Is_Valid()) return false;
    unsigned short red_mask = 0xFF;
    red_mask >>= unknown_shift_852fbc;
    red_mask <<= unknown_shift_852fb8;
    unsigned short green_mask = 0xFF;
    green_mask >>= unknown_shift_852fcc;
    green_mask <<= unknown_shift_852fc8;
    unsigned short blue_mask = 0xFF;
    blue_mask >>= unknown_shift_852fc4;
    blue_mask <<= unknown_shift_852fc0;
    unsigned short *pixels = (unsigned short *)Lock(area.Top_Left());
    if (!pixels) return false;
    if (percent > 100) percent = 100;
    percent = percent * 255 / 100;
    unsigned short inverse = (unsigned short)(255 - percent);
    unsigned short pixel = (unsigned short)(((unsigned short)(unsigned char)(color.Red >> unknown_shift_852fbc) << unknown_shift_852fb8)
         | ((unsigned short)(unsigned char)(color.Green >> unknown_shift_852fcc) << unknown_shift_852fc8)
         | ((unsigned short)(unsigned char)(color.Blue >> unknown_shift_852fc4) << unknown_shift_852fc0));
    for (int y = 0; y < area.Height; ++y) {
        int offset = (Stride() / 2) * y;
        for (int x = 0; x < area.Width; ++x) {
            unsigned short background = pixels[offset];
            pixels[offset++] = (unsigned short)(((((background & red_mask) * inverse + (pixel & red_mask) * percent) >> 8) & red_mask)
                | ((((background & green_mask) * inverse + (pixel & green_mask) * percent) >> 8) & green_mask)
                | (((background & blue_mask) * inverse + (pixel & blue_mask) * percent) >> 8));
        }
    }
    Unlock();
    return true;
}
