// Draw a clipped 16-bit line between two screen points with depths (TibSun
// dsurface.cpp Draw_Depth_Shaded_Line): plots color where the line is in front
// of the depth ring (0x00839C6C) and the level ring (0x008315B4) is non-zero,
// darkened by level/128 unless the level is 127; write_depth stores the depth.
// The depths of clipped endpoints are interpolated by length.
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
bool DSurface::Draw_Depth_Shaded_Line(Rect const & cliprect, Point2D const & startpoint, Point2D const & endpoint, unsigned color, int start_depth, int end_depth, bool write_depth)
{
    Rect clipped_rect = cliprect.Intersect(Get_Rect());
    if (clipped_rect.Width == 0 && clipped_rect.Height == 0) {
        return(false);
    }
    Point2D start = Offset_Point(startpoint, clipped_rect);
    Point2D end = Offset_Point(endpoint, clipped_rect);
    int zfirst = start_depth;
    int zlast = end_depth;
    if (start.X > end.X) {
        Point2D temp = start;
        start = end;
        end = temp;
        zfirst = end_depth;
        zlast = start_depth;
    }
    Point2D unclipped = end;
    int px = start.X;
    int py = start.Y;
    if (!Clip_Line(start, end, clipped_rect)) {
        return(false);
    }
    int zend = zlast;
    int zstart = zfirst;
    if (end.X != unclipped.X || end.Y != unclipped.Y) {
        Point2D clipped_point;
        clipped_point.X = px - end.X;
        double clipped_dx = (double)clipped_point.X;
        clipped_point.Y = py - end.Y;
        int clipped = (int)(int)Fast_Sqrt((double)clipped_point.Y * (double)clipped_point.Y + clipped_dx * clipped_dx);
        Point2D full_point;
        full_point.X = px - unclipped.X;
        double full_dx = (double)full_point.X;
        full_point.Y = py - unclipped.Y;
        int amount = abs((int)(int)((double)clipped
            / (double)(int)(int)Fast_Sqrt((double)full_point.Y * (double)full_point.Y + full_dx * full_dx)
            * (double)(zfirst - zlast)));
        if (zfirst < zlast) {
            zend = zfirst + amount;
        } else {
            zend = zfirst - amount;
        }
    }
    if (start.X != px || start.Y != py) {
        Point2D clipped_point;
        clipped_point.X = start.X - unclipped.X;
        double clipped_dx = (double)clipped_point.X;
        clipped_point.Y = start.Y - unclipped.Y;
        int clipped = (int)(int)Fast_Sqrt((double)clipped_point.Y * (double)clipped_point.Y + clipped_dx * clipped_dx);
        Point2D full_point;
        full_point.X = px - unclipped.X;
        double full_dx = (double)full_point.X;
        full_point.Y = py - unclipped.Y;
        int amount = abs((int)(int)((double)clipped
            / (double)(int)(int)Fast_Sqrt((double)full_point.Y * (double)full_point.Y + full_dx * full_dx)
            * (double)(zfirst - zlast)));
        if (zlast > zfirst) {
            zstart = zlast - amount;
        } else {
            zstart = zlast + amount;
        }
    }
    Bytes_Per_Pixel();
    void * buffer = Lock(start);
    if (ABufferPtr == 0) {
        return(false);
    }
    Point2D point = start;
    point.Y -= ABufferPtr->Area.Y;
    unsigned short * zbuffer = ABufferPtr->Get_Buffer_Ptr(point);
    point = start;
    point.Y -= ZBufferPtr->Area.Y;
    unsigned short * abuffer = ZBufferPtr->Get_Buffer_Ptr(point);
    int start_y = start.Y;
    int zwrap = -1;
    unsigned short z = (unsigned short)(zstart + (short)ABufferPtr->Get_Scroll_Delta(start_y + clipped_rect.Y - ABufferPtr->Area.Y));
    int zwidth = ABufferPtr->Width;
    int red;
    int green;
    int blue;
    if (buffer != 0) {
        RGBClass rgb(
            (unsigned char)(((unsigned short)color >> unknown_shift_852fb8) << unknown_shift_852fbc),
            (unsigned char)(((unsigned short)color >> unknown_shift_852fc8) << unknown_shift_852fcc),
            (unsigned char)(((unsigned short)color >> unknown_shift_852fc0) << unknown_shift_852fc4));
        red = rgb.Red;
        green = rgb.Green;
        blue = rgb.Blue;
    } else {
        return(false);
    }
    int dy = end.Y - start.Y;
    int dx = end.X - start.X;
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
    int abs_dz = abs(dz);
    int dx2 = 2 * dx;
    int dy2 = 2 * abs_dy;
    int dz2 = 2 * abs_dz;
    if (abs_dz > dx && abs_dz > abs_dy) {
        int xdelta = dy2 - abs_dz;
        int ydelta = dx2 - abs_dz;
        if (abs_dz > 0) {
            int offset = 0;
            for (int i = abs_dz; i != 0; i--) {
                int v = *abuffer;
                if (z < *zbuffer && v != 0) {
                    if (v != 127) {
                        *(unsigned short *)((char *)buffer + offset) = (unsigned short)((((red * v) >> 7 >> unknown_shift_852fbc) << unknown_shift_852fb8) | (((green * v) >> 7 >> unknown_shift_852fcc) << unknown_shift_852fc8) | (((blue * v) >> 7 >> unknown_shift_852fc4) << unknown_shift_852fc0));
                    } else {
                        *(unsigned short *)((char *)buffer + offset) = (unsigned short)color;
                    }
                    if (write_depth) {
                        *zbuffer = z;
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
                    abuffer += zwidth;
                    if (zwidth > 0) {
                        abuffer = (unsigned short *)ZBufferPtr->Wrap_Overflow((unsigned int)abuffer);
                    } else {
                        abuffer = (unsigned short *)ZBufferPtr->Wrap_Underflow((unsigned int)abuffer);
                    }
                    z += zwrap;
                }
                if (ydelta > 0) {
                    zbuffer++;
                    offset += 2;
                    zbuffer = (unsigned short *)ABufferPtr->Wrap_Overflow((unsigned int)zbuffer);
                    abuffer++;
                    abuffer = (unsigned short *)ZBufferPtr->Wrap_Overflow((unsigned int)abuffer);
                    ydelta -= dz2;
                }
                z += zstep;
                ydelta += dx2;
                xdelta += dy2;
            }
        }
    } else if (dx > abs_dy) {
        int ydelta = dy2 - dx;
        int i = 0;
        int zdelta = dz2 - dx;
        if (dx > 0) {
            for (; i < dx; i++) {
                int v = *abuffer;
                if (z < *zbuffer && v != 0) {
                    if (v != 127) {
                        *(unsigned short *)((char *)buffer + 2 * i) = (unsigned short)((((red * v) >> 7 >> unknown_shift_852fbc) << unknown_shift_852fb8) | (((green * v) >> 7 >> unknown_shift_852fcc) << unknown_shift_852fc8) | (((blue * v) >> 7 >> unknown_shift_852fc4) << unknown_shift_852fc0));
                    } else {
                        *(unsigned short *)((char *)buffer + 2 * i) = (unsigned short)color;
                    }
                    if (write_depth) {
                        *zbuffer = z;
                    }
                }
                if (ydelta > 0) {
                    buffer = (unsigned char *)buffer + pitch;
                    ydelta -= 2 * dx;
                    zbuffer += zwidth;
                    if (zwidth > 0) {
                        zbuffer = (unsigned short *)ABufferPtr->Wrap_Overflow((unsigned int)zbuffer);
                    } else {
                        zbuffer = (unsigned short *)ABufferPtr->Wrap_Underflow((unsigned int)zbuffer);
                    }
                    z += zwrap;
                    abuffer += zwidth;
                    if (zwidth > 0) {
                        abuffer = (unsigned short *)ZBufferPtr->Wrap_Overflow((unsigned int)abuffer);
                    } else {
                        abuffer = (unsigned short *)ZBufferPtr->Wrap_Underflow((unsigned int)abuffer);
                    }
                }
                if (zdelta > 0) {
                    z += zstep;
                    zdelta -= 2 * dx;
                }
                zbuffer++;
                ydelta += dy2;
                zdelta += dz2;
                zbuffer = (unsigned short *)ABufferPtr->Wrap_Overflow((unsigned int)zbuffer);
                abuffer++;
                abuffer = (unsigned short *)ZBufferPtr->Wrap_Overflow((unsigned int)abuffer);
            }
        }
    } else {
        int xdelta = dx2 - abs_dy;
        int zdelta = 2 * abs_dz - abs_dy;
        if (abs_dy > 0) {
            int i = abs_dy;
            int offset = 0;
            do {
                int v = *abuffer;
                if (z < *zbuffer && v != 0) {
                    if (v != 127) {
                        *(unsigned short *)((char *)buffer + offset) = (unsigned short)((((red * v) >> 7 >> unknown_shift_852fbc) << unknown_shift_852fb8) | (((green * v) >> 7 >> unknown_shift_852fcc) << unknown_shift_852fc8) | (((blue * v) >> 7 >> unknown_shift_852fc4) << unknown_shift_852fc0));
                    } else {
                        *(unsigned short *)((char *)buffer + offset) = (unsigned short)color;
                    }
                    if (write_depth) {
                        *zbuffer = z;
                    }
                }
                if (xdelta > 0) {
                    zbuffer++;
                    offset += 2;
                    zbuffer = (unsigned short *)ABufferPtr->Wrap_Overflow((unsigned int)zbuffer);
                    abuffer++;
                    abuffer = (unsigned short *)ZBufferPtr->Wrap_Overflow((unsigned int)abuffer);
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
                abuffer += zwidth;
                if (zwidth > 0) {
                    abuffer = (unsigned short *)ZBufferPtr->Wrap_Overflow((unsigned int)abuffer);
                } else {
                    abuffer = (unsigned short *)ZBufferPtr->Wrap_Underflow((unsigned int)abuffer);
                }
                i--;
            } while (i != 0);
        }
    }
    Unlock();
    return(true);
}
