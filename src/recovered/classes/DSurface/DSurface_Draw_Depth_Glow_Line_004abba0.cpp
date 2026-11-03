// Draw a clipped 16-bit line between two screen points with depths (TibSun
// dsurface.cpp Draw_Depth_Glow_Line): each pixel in front of the depth ring
// (ABufferPtr 0x00839C6C) has every channel brightened by glow_strength/256,
// clamped to 255; write_depth stores the line's depth. The depths of clipped
// endpoints are interpolated by length. The px, origend, py order matches the
// original's register choice at the steep loop's depth test.
#include "shared/always.hpp"
#include "shared/blit.hpp"
#include "shared/crt_memory.hpp"
#include "shared/dsurface.hpp"
#include "shared/fast_math.hpp"
#include "shared/hicolor.hpp"
#include "shared/rgb_class.hpp"
// @ref ?Clip_Line@@YI_NAAUPoint2D@@0ABVRect@@@Z=00775620
// @ref ?Intersect@@YI?AVRect@@ABV1@0PAH1@Z=0041fdf0
// @ref ?Fast_Sqrt@@YAMN@Z=004ba410
// @ref ?Get_Buffer_Ptr@ZBuffer@@QAEPAGUPoint2D@@@Z=00411230
// @ref ?Get_Buffer_Ptr@ABuffer@@QAEPAGUPoint2D@@@Z=00776340
// @ref ?ZBufferPtr@@3PAVZBuffer@@A=008315b4
// @ref ?ABufferPtr@@3PAVABuffer@@A=00839c6c
// @ref ?unknown_shift_852fb8@@3HA=00852fb8
// @ref ?unknown_shift_852fbc@@3HA=00852fbc
// @ref ?unknown_shift_852fc0@@3HA=00852fc0
// @ref ?unknown_shift_852fc4@@3HA=00852fc4
// @ref ?unknown_shift_852fc8@@3HA=00852fc8
// @ref ?unknown_shift_852fcc@@3HA=00852fcc
// Point length through the table square root, expanded inline (the TibSun
// point.h Length; Point2D::Length 0x0047D060 is the out-of-line copy).
static inline int Inline_Length(Point2D const &point)
{
    double y = (double)point.Y;
    double x = (double)point.X;
    return (int)Fast_Sqrt(x * x + y * y);
}

bool DSurface::Draw_Depth_Glow_Line(Rect const & cliprect, Point2D const & startpoint, Point2D const & endpoint, int glow_strength, int start_depth, int end_depth, bool write_depth)
{
    Point2D start;
    Point2D end;
    Rect rect = cliprect.Intersect(Get_Rect());
    if (rect.Width != 0 || rect.Height != 0) {
    start = Offset_Point(startpoint, rect);
    end = Offset_Point(endpoint, rect);
    int z1 = start_depth;
    int z2 = end_depth;
    if (start.X > end.X) {
        Point2D temp = start;
        start = end;
        end = temp;
        z1 = end_depth;
        z2 = start_depth;
    }
    int px = start.X;
    Point2D origend = end;
    int py = start.Y;
    if (Clip_Line(start, end, rect)) {
    int zend = z2;
    int zstart = z1;
    if (end.X != origend.X || end.Y != origend.Y) {
        Point2D clipped = Point2D(px, py) - end;
        Point2D full = Point2D(px, py) - origend;
        int fulllen = full.Length();
        unsigned int amount = abs((int)((double)clipped.Length() / (double)fulllen * (double)(z1 - z2)));
        if (z1 < z2) {
            zend = z1 + amount;
        } else {
            zend = z1 - amount;
        }
    }
    if (start.X != px || start.Y != py) {
        Point2D clipped_point(start.X - origend.X, start.Y - origend.Y);
        int clipped = Inline_Length(clipped_point);
        Point2D full_point(px - origend.X, py - origend.Y);
        int full = Inline_Length(full_point);
        unsigned int amount = abs((int)((double)clipped / (double)full * (double)(z1 - z2)));
        if (z2 > z1) {
            zstart = z2 - amount;
        } else {
            zstart = z2 + amount;
        }
    }
    Bytes_Per_Pixel();
    void * buffer = Lock(start);
    if (ABufferPtr != 0) {
    Point2D point = start;
    point.Y -= ABufferPtr->Area.Y;
    unsigned short * zbuffer = ABufferPtr->Get_Buffer_Ptr(point);
    int start_y = start.Y;
    int zwrap = -1;
    ABuffer *depth_buffer = ABufferPtr;
    unsigned short z = (unsigned short)(zstart + (short)(depth_buffer->Area.Y + depth_buffer->Get_Scroll()) - start_y - rect.Y);
    int zwidth = depth_buffer->Width;
    if (buffer != 0) {
    int dx = end.X - start.X;
    int xcount = dx;
    int dy = end.Y - start.Y;
    int dz = zend - zstart;
    int pitch = Stride();
    if (dy < 0) {
        pitch = -pitch;
        zwidth = -zwidth;
        zwrap = 1;
    }
    int zstep = 1;
    int abs_dy = abs(dy);
    if (dz < 0) {
        zstep = -1;
    }
    int dy2 = 2 * abs_dy;
    int abs_dz = abs(dz);
    int dx2 = 2 * dx;
    int dz2 = 2 * abs_dz;
    if (abs_dz > dx && abs_dz > abs_dy) {
        int xdelta = dy2 - abs_dz;
        int ydelta = dx2 - abs_dz;
        if (abs_dz > 0) {
            int offset = 0;
            for (int i = abs_dz; i != 0; i--) {
                if ((unsigned short)z < *zbuffer) {
                    RGBClass rgb = Deconstruct_Hicolor_Pixel(*(unsigned short *)((char *)buffer + offset));
                    int red = rgb.Red;
                    red += (glow_strength * red) >> 8;
                    int green = rgb.Green;
                    green += (glow_strength * green) >> 8;
                    int blue = rgb.Blue;
                    blue += (glow_strength * blue) >> 8;
                    *(unsigned short *)((char *)buffer + offset) = (unsigned short)Build_Hicolor_Pixel(min(255, red), min(255, green), min(255, blue));
                    if (write_depth) {
                        *zbuffer = (unsigned short)z;
                    }
                }
                if (xdelta > 0) {
                    buffer = (unsigned char *)buffer + pitch;
                    xdelta -= dz2;
                    zbuffer += zwidth;
                    if (zwidth > 0) {
                        zbuffer = (unsigned short *)ABufferPtr->Wrap_Overflow((unsigned int)zbuffer);
                    } else {
                        zbuffer = (unsigned short *)ABufferPtr->Wrap_Underflow((unsigned int)zbuffer);
                    }
                    z += zwrap;
                }
                if (ydelta > 0) {
                    zbuffer++;
                    offset += 2;
                    zbuffer = (unsigned short *)ABufferPtr->Wrap_Overflow((unsigned int)zbuffer);
                    ydelta -= dz2;
                }
                z += zstep;
                ydelta += dx2;
                xdelta += dy2;
            }
        }
    } else if (dx > abs_dy) {
        int offset = 0;
        int ydelta = dy2 - dx;
        int zdelta = dz2 - dx;
        if (dx > 0) {
            do {
                if ((unsigned short)z < *zbuffer) {
                    RGBClass rgb = Deconstruct_Hicolor_Pixel(*((unsigned short *)buffer + offset));
                    int red = rgb.Red;
                    red += (glow_strength * red) >> 8;
                    int green = rgb.Green;
                    green += (glow_strength * green) >> 8;
                    int blue = rgb.Blue;
                    blue += (glow_strength * blue) >> 8;
                    *((unsigned short *)buffer + offset) = (unsigned short)Build_Hicolor_Pixel(min(255, red), min(255, green), min(255, blue));
                    if (write_depth) {
                        *zbuffer = (unsigned short)z;
                    }
                }
                if (ydelta > 0) {
                    buffer = (unsigned char *)buffer + pitch;
                    ydelta -= dx2;
                    zbuffer += zwidth;
                    if (zwidth > 0) {
                        zbuffer = (unsigned short *)ABufferPtr->Wrap_Overflow((unsigned int)zbuffer);
                    } else {
                        zbuffer = (unsigned short *)ABufferPtr->Wrap_Underflow((unsigned int)zbuffer);
                    }
                    z += zwrap;
                }
                if (zdelta > 0) {
                    z += zstep;
                    zdelta -= dx2;
                }
                zbuffer++;
                ydelta += dy2;
                zdelta += dz2;
                zbuffer = (unsigned short *)ABufferPtr->Wrap_Overflow((unsigned int)zbuffer);
            } while (++offset < xcount);
        }
    } else {
        int xdelta = dx2 - abs_dy;
        int zdelta = dz2 - abs_dy;
        if (abs_dy > 0) {
            int offset = 0;
            for (int i = abs_dy; i != 0; i--) {
                if ((unsigned short)z < *zbuffer) {
                    RGBClass rgb = Deconstruct_Hicolor_Pixel(*(unsigned short *)((char *)buffer + offset));
                    int red = rgb.Red;
                    red += (glow_strength * red) >> 8;
                    int green = rgb.Green;
                    green += (glow_strength * green) >> 8;
                    int blue = rgb.Blue;
                    blue += (glow_strength * blue) >> 8;
                    *(unsigned short *)((char *)buffer + offset) = (unsigned short)Build_Hicolor_Pixel(min(255, red), min(255, green), min(255, blue));
                    if (write_depth) {
                        *zbuffer = (unsigned short)z;
                    }
                }
                if (xdelta > 0) {
                    zbuffer++;
                    offset += 2;
                    zbuffer = (unsigned short *)ABufferPtr->Wrap_Overflow((unsigned int)zbuffer);
                    xdelta -= dy2;
                }
                if (zdelta > 0) {
                    z += zstep;
                    zdelta -= dy2;
                }
                xdelta += dx2;
                zdelta += dz2;
                buffer = (unsigned char *)buffer + pitch;
                zbuffer += zwidth;
                if (zwidth > 0) {
                    zbuffer = (unsigned short *)ABufferPtr->Wrap_Overflow((unsigned int)zbuffer);
                } else {
                    zbuffer = (unsigned short *)ABufferPtr->Wrap_Underflow((unsigned int)zbuffer);
                }
                z += zwrap;
            }
        }
    }
    Unlock();
    return(true);
    }
    }
    }
    }
    return(false);
}
