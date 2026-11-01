// void __fastcall Scale_Rotate(Surface &surf, BitmapClass &bmp, Point2D const &pt, int scale, unsigned char angle) (0x0068B800)
// Draws a scaled and rotated 8-bit bitmap centred on pt (TibSun sprite.cpp shape; no clipping, no callers).
#include "shared/sprite.hpp"
// @ref ?_SineTab@@3PAHA=007f44c4
// @ref ?_CosineTab@@3PAHA=007f48c4

void __fastcall Scale_Rotate(Surface &surf, BitmapClass &bmp, Point2D const &pt, int scale, unsigned char angle)
{
    void *buf = surf.Lock();
    signed int scrpos;
    signed int temp;
    int i, j;
    int pxerror = 0;
    int pyerror = 0;
    int pixpos = 0;
    unsigned char pixel;
    Point2D p0;
    Point2D p1;
    Point2D p2;

    {
        angle &= 255;
        int c = _CosineTab[angle];
        int s = _SineTab[angle];
        int W = (scale * bmp.Width) >> 1;
        int L = (scale * bmp.Height) >> 1;
        p0.X = (pt.X + ((((L * c) >> 8) - ((W * s) >> 8)) >> 8));
        p0.Y = (pt.Y + (((-(L * s) >> 8) - ((W * c) >> 8)) >> 8));
        p1.X = (pt.X + ((((L * c) >> 8) + ((W * s) >> 8)) >> 8));
        p1.Y = (pt.Y + (((-(L * s) >> 8) + ((W * c) >> 8)) >> 8));
        p2.X = (pt.X + (((-(L * c) >> 8) - ((W * s) >> 8)) >> 8));
        p2.Y = (pt.Y + ((((L * s) >> 8) - ((W * c) >> 8)) >> 8));
    }

    int f_deltax = (p1.X - p0.X);
    int f_deltay = (p1.Y - p0.Y);
    int f_error = 0;
    int f_xstep = 1;
    int f_ystep = surf.Stride();

    int s_deltax = (p2.X - p0.X);
    int s_deltay = (p2.Y - p0.Y);
    int s_error = 0;
    int s_xstep = 1;
    int s_ystep = surf.Stride();

    if (f_deltay < 0) {
        f_deltay = -f_deltay;
        f_ystep = -surf.Stride();
    }
    if (f_deltax < 0) {
        f_deltax = -f_deltax;
        f_xstep = -1;
    }
    if (s_deltay < 0) {
        s_deltay = -s_deltay;
        s_ystep = -surf.Stride();
    }
    if (s_deltax < 0) {
        s_deltax = -s_deltax;
        s_xstep = -1;
    }

    scrpos = p0.X + surf.Stride() * p0.Y;
    temp = scrpos;

    if (scrpos >= 0) {
        if (f_deltax > f_deltay) {
            for (j = 0; j < s_deltay; j++) {
                if (scrpos < 0) break;
                temp = scrpos;
                for (i = 0; i < f_deltax; i++) {
                    pixel = bmp.Data[pixpos];
                    if (pixel) ((unsigned char *)buf)[scrpos] = pixel;
                    pxerror += bmp.Width;
                    while (pxerror > f_deltax) {
                        pixpos++;
                        pxerror -= f_deltax;
                    }
                    scrpos += f_xstep;
                    f_error += f_deltay;
                    if (f_error > f_deltax) {
                        if (pixel) ((unsigned char *)buf)[scrpos] = pixel;
                        f_error -= f_deltax;
                        scrpos += f_ystep;
                    }
                }
                pxerror = 0;
                pixpos -= bmp.Width - 1;
                pyerror += bmp.Height;
                while (pyerror > s_deltay) {
                    pixpos += bmp.Width;
                    pyerror -= s_deltay;
                }
                f_error = 0;
                scrpos = temp;
                scrpos += s_ystep;
                s_error += s_deltax;
                if (s_error > s_deltay) {
                    s_error -= s_deltay;
                    scrpos += s_xstep;
                }
            }
        } else {
            for (j = 0; j < s_deltax; j++) {
                if (scrpos < 0) break;
                temp = scrpos;
                for (i = 0; i < f_deltay; i++) {
                    pixel = bmp.Data[pixpos];
                    if (pixel) ((unsigned char *)buf)[scrpos] = pixel;
                    pxerror += bmp.Width;
                    while (pxerror > f_deltay) {
                        pixpos++;
                        pxerror -= f_deltay;
                    }
                    scrpos += f_ystep;
                    f_error += f_deltax;
                    if (f_error > f_deltay) {
                        if (pixel) ((unsigned char *)buf)[scrpos] = pixel;
                        f_error -= f_deltay;
                        scrpos += f_xstep;
                    }
                }
                pxerror = 0;
                pixpos -= bmp.Width - 1;
                pyerror += bmp.Height;
                while (pyerror > s_deltax) {
                    pixpos += bmp.Width;
                    pyerror -= s_deltax;
                }
                scrpos = temp;
                scrpos += s_xstep;
                s_error += s_deltay;
                f_error = 0;
                if (s_error > s_deltax) {
                    s_error -= s_deltax;
                    scrpos += s_ystep;
                }
            }
        }
    }
    surf.Unlock();
}
