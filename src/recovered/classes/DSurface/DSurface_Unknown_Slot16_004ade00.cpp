// DSurface slot 16 (0x004ADE00; an RA2 addition, not in TibSun). The TibSun
// Draw_Depth_Glow_Line / Draw_Depth_Shaded_Line skeleton: clip, interpolate the
// clipped depths by length, then step along the major axis. Where the line is in
// front of the depth ring (0x00839C6C) the background pixel is brightened through
// Brighten_Hicolor_Pixel by color * intensity scaled by the level ring (0x008315B4,
// level/128). Nothing is drawn when every scaled channel is below 8. The level
// pointer follows row steps only (x steps move the depth pointer alone).
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
// @ref ?Brighten_Hicolor_Pixel@@YIHABVRGBClass@@HHH@Z=004ae8d0
// @ref ?unknown_shift_852fb8@@3HA=00852fb8
// @ref ?unknown_shift_852fbc@@3HA=00852fbc
// @ref ?unknown_shift_852fc0@@3HA=00852fc0
// @ref ?unknown_shift_852fc4@@3HA=00852fc4
// @ref ?unknown_shift_852fc8@@3HA=00852fc8
// @ref ?unknown_shift_852fcc@@3HA=00852fcc
// Point length through the table square root, expanded inline (the squared Y
// term is formed first).
static inline int Depth_Line_Length(Point2D const &point)
{
    double x = (double)point.X;
    double y = (double)point.Y;
    double yy = y * y;
    return (int)Fast_Sqrt(yy + x * x);
}

bool DSurface::Unknown_Slot16(Rect const & cliprect, Point2D const & startpoint, Point2D const & endpoint, RGBClass const & color, float intensity, int start_depth, int end_depth)
{
    int red = (int)(color.Red * intensity);
    int green = (int)(color.Green * intensity);
    int blue = (int)(color.Blue * intensity);
    if (red >= 8 || green >= 8 || blue >= 8) {
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
    int py = start.Y;
    Point2D origend = end;
    if (Clip_Line(start, end, rect)) {
    int zend = z2;
    int zstart = z1;
    if (end.X != origend.X || end.Y != origend.Y) {
        Point2D clipped_point(px - end.X, py - end.Y);
        int clipped = Depth_Line_Length(clipped_point);
        Point2D full_point(px - origend.X, py - origend.Y);
        int full = Depth_Line_Length(full_point);
        unsigned int amount = abs((int)((double)clipped / (double)full * (double)(z1 - z2)));
        if (z1 < z2) {
            zend = z1 + amount;
        } else {
            zend = z1 - amount;
        }
    }
    if (start.X != px || start.Y != py) {
        Point2D clipped_point(start.X - origend.X, start.Y - origend.Y);
        int clipped = Depth_Line_Length(clipped_point);
        Point2D full_point(px - origend.X, py - origend.Y);
        int full = Depth_Line_Length(full_point);
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
    point = start;
    point.Y -= ZBufferPtr->Area.Y;
    unsigned short * level = ZBufferPtr->Get_Buffer_Ptr(point);
    int start_y = start.Y;
    int zwrap = -1;
    ABuffer *depth_buffer = ABufferPtr;
    unsigned short z = (unsigned short)(zstart + (short)(depth_buffer->Area.Y + depth_buffer->Get_Scroll()) - start_y - rect.Y);
    int zwidth = depth_buffer->Width;
    if (buffer != 0) {
    int dx = end.X - start.X;
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
    RGBClass back;
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
                int v = *level;
                if (z < *zbuffer) {
                    back = Deconstruct_Hicolor_Pixel(*(unsigned short *)((char *)buffer + offset));
                    *(unsigned short *)((char *)buffer + offset) = (unsigned short)Brighten_Hicolor_Pixel(back, (v * red) >> 7, (v * green) >> 7, (v * blue) >> 7);
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
                    level += zwidth;
                    if (zwidth > 0) {
                        level = (unsigned short *)ZBufferPtr->Wrap_Overflow((unsigned int)level);
                    } else {
                        level = (unsigned short *)ZBufferPtr->Wrap_Underflow((unsigned int)level);
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
        int ydelta = dy2 - dx;
        int zdelta = dz2 - dx;
        int i = 0;
        if (dx > 0) {
            for (; i < dx; i++) {
                int v = *level;
                if (z < *zbuffer) {
                    back = Deconstruct_Hicolor_Pixel(*(unsigned short *)((char *)buffer + 2 * i));
                    *(unsigned short *)((char *)buffer + 2 * i) = (unsigned short)Brighten_Hicolor_Pixel(back, (v * red) >> 7, (v * green) >> 7, (v * blue) >> 7);
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
                    level += zwidth;
                    if (zwidth > 0) {
                        level = (unsigned short *)ZBufferPtr->Wrap_Overflow((unsigned int)level);
                    } else {
                        level = (unsigned short *)ZBufferPtr->Wrap_Underflow((unsigned int)level);
                    }
                    z += zwrap;
                }
                if (zdelta > 0) {
                    z += zstep;
                    zdelta -= 2 * dx;
                }
                zbuffer++;
                ydelta += dy2;
                zdelta += dz2;
                zbuffer = (unsigned short *)ABufferPtr->Wrap_Overflow((unsigned int)zbuffer);
            }
        }
    } else {
        int xdelta = dx2 - abs_dy;
        int zdelta = 2 * abs_dz - abs_dy;
        if (abs_dy > 0) {
            int offset = 0;
            for (int i = abs_dy; i != 0; i--) {
                int v = *level;
                if (z < *zbuffer) {
                    back = Deconstruct_Hicolor_Pixel(*(unsigned short *)((char *)buffer + offset));
                    *(unsigned short *)((char *)buffer + offset) = (unsigned short)Brighten_Hicolor_Pixel(back, (v * red) >> 7, (v * green) >> 7, (v * blue) >> 7);
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
                level += zwidth;
                if (zwidth > 0) {
                    level = (unsigned short *)ZBufferPtr->Wrap_Overflow((unsigned int)level);
                } else {
                    level = (unsigned short *)ZBufferPtr->Wrap_Underflow((unsigned int)level);
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
    }
    return(false);
}
