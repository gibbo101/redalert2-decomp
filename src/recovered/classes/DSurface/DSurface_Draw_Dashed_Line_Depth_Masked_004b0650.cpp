// Draw_Dashed_Line limited by the depth buffer (TibSun dsurface.cpp
// Draw_Masked_Dashed_Line): plots the pattern's set entries only where the
// depth value is zero (empty_only) or only where it is not, and returns the
// updated pattern offset (16-bit surfaces only).
#include "shared/blit.hpp"
#include "shared/crt_memory.hpp"
#include "shared/dsurface.hpp"
// @ref ?Get_Buffer_Ptr@ZBuffer@@QAEPAGUPoint2D@@@Z=00411230
// @ref ?ZBufferPtr@@3PAVZBuffer@@A=008315b4
int DSurface::Draw_Dashed_Line_Depth_Masked(Point2D const &startpoint, Point2D const &endpoint, int color,
                                            bool const *pattern, int offset, bool empty_only)
{
    Point2D start = startpoint;
    Point2D end = endpoint;
    int pattern_step = 1;
    if (Bytes_Per_Pixel() != 2) return 0;
    if (start.X > end.X) {
        Point2D temp = start;
        start = end;
        end = temp;
        int dx = abs(start.X - end.X);
        int dy = abs(start.Y - end.Y) + 1;
        if (dx < dy) dx = dy;
        offset = (offset + dx) % 16;
        pattern_step = -1;
    }
    Point2D point = start;
    point.Y -= ZBufferPtr->Area.Y;
    unsigned short *depth = ZBufferPtr->Get_Buffer_Ptr(point);
    int depth_stride = ZBufferPtr->Width;
    if (start.Y > end.Y) depth_stride = -depth_stride;
    unsigned short *pixels = (unsigned short *)Lock(start);
    if (pixels != 0) {
        if (empty_only) {
            if (start.Y == end.Y) {
                for (int i = 0; i <= end.X - start.X; i++, offset += pattern_step) {
                    if (offset < 0) offset += 16;
                    if (offset >= 16) offset -= 16;
                    if (pattern[offset] && *depth == 0) pixels[i] = (unsigned short)color;
                    if (depth_stride > 0) {
                        depth++;
                        depth = (unsigned short *)ZBufferPtr->Wrap_Overflow((unsigned int)depth);
                    } else {
                        depth++;
                        depth = (unsigned short *)ZBufferPtr->Wrap_Underflow((unsigned int)depth);
                    }
                }
            } else if (start.X == end.X) {
                int pitch = start.Y > end.Y ? -Stride() : Stride();
                int dy = abs(end.Y - start.Y);
                for (int i = 0; i <= dy; i++, offset += pattern_step) {
                    if (offset < 0) offset += 16;
                    if (offset >= 16) offset -= 16;
                    if (pattern[offset] && *depth == 0) *pixels = (unsigned short)color;
                    pixels = (unsigned short *)((unsigned char *)pixels + pitch);
                    if (depth_stride > 0) {
                        depth += depth_stride;
                        depth = (unsigned short *)ZBufferPtr->Wrap_Overflow((unsigned int)depth);
                    } else {
                        depth += depth_stride;
                        depth = (unsigned short *)ZBufferPtr->Wrap_Underflow((unsigned int)depth);
                    }
                }
            } else {
                int dx = end.X - start.X;
                int dy = end.Y - start.Y;
                int pitch = Stride();
                if (dy < 0) pitch = -pitch;
                dy = abs(dy);
                int dx2 = 2 * dx;
                int dy2 = 2 * dy;
                if (dx > dy) {
                    int delta = dy2 - dx;
                    for (int i = 0; i < dx; i++, offset += pattern_step) {
                        if (offset < 0) offset += 16;
                        if (offset >= 16) offset -= 16;
                        if (pattern[offset] && *depth == 0) pixels[i] = (unsigned short)color;
                        if (delta > 0) {
                            pixels = (unsigned short *)((unsigned char *)pixels + pitch);
                            depth += depth_stride;
                            depth = (unsigned short *)ZBufferPtr->Wrap_Overflow((unsigned int)depth);
                            delta -= dx2;
                        }
                        delta += dy2;
                        if (depth_stride > 0) {
                            depth++;
                            depth = (unsigned short *)ZBufferPtr->Wrap_Overflow((unsigned int)depth);
                        } else {
                            depth++;
                            depth = (unsigned short *)ZBufferPtr->Wrap_Underflow((unsigned int)depth);
                        }
                    }
                } else {
                    int delta = dx2 - dy;
                    int k = 0;
                    for (int i = 0; i < dy; i++, offset += pattern_step) {
                        if (offset < 0) offset += 16;
                        if (offset >= 16) offset -= 16;
                        if (pattern[offset] && *depth == 0) pixels[k] = (unsigned short)color;
                        if (delta > 0) {
                            k++;
                            depth++;
                            depth = (unsigned short *)ZBufferPtr->Wrap_Overflow((unsigned int)depth);
                            delta -= dy2;
                        }
                        delta += dx2;
                        pixels = (unsigned short *)((unsigned char *)pixels + pitch);
                        if (depth_stride > 0) {
                            depth += depth_stride;
                            depth = (unsigned short *)ZBufferPtr->Wrap_Overflow((unsigned int)depth);
                        } else {
                            depth += depth_stride;
                            depth = (unsigned short *)ZBufferPtr->Wrap_Underflow((unsigned int)depth);
                        }
                    }
                }
            }
        } else {
            if (start.Y == end.Y) {
                for (int i = 0; i <= end.X - start.X; i++, offset += pattern_step) {
                    if (offset < 0) offset += 16;
                    if (offset >= 16) offset -= 16;
                    if (pattern[offset] && *depth != 0) pixels[i] = (unsigned short)color;
                    if (depth_stride > 0) {
                        depth++;
                        depth = (unsigned short *)ZBufferPtr->Wrap_Overflow((unsigned int)depth);
                    } else {
                        depth++;
                        depth = (unsigned short *)ZBufferPtr->Wrap_Underflow((unsigned int)depth);
                    }
                }
            } else if (start.X == end.X) {
                int pitch = start.Y > end.Y ? -Stride() : Stride();
                int dy = abs(end.Y - start.Y);
                for (int i = 0; i <= dy; i++, offset += pattern_step) {
                    if (offset < 0) offset += 16;
                    if (offset >= 16) offset -= 16;
                    if (pattern[offset] && *depth != 0) *pixels = (unsigned short)color;
                    pixels = (unsigned short *)((unsigned char *)pixels + pitch);
                    if (depth_stride > 0) {
                        depth += depth_stride;
                        depth = (unsigned short *)ZBufferPtr->Wrap_Overflow((unsigned int)depth);
                    } else {
                        depth += depth_stride;
                        depth = (unsigned short *)ZBufferPtr->Wrap_Underflow((unsigned int)depth);
                    }
                }
            } else {
                int dx = end.X - start.X;
                int dy = end.Y - start.Y;
                int pitch = Stride();
                if (dy < 0) pitch = -pitch;
                dy = abs(dy);
                int dx2 = 2 * dx;
                int dy2 = 2 * dy;
                if (dx > dy) {
                    int delta = dy2 - dx;
                    for (int i = 0; i < dx; i++, offset += pattern_step) {
                        if (offset < 0) offset += 16;
                        if (offset >= 16) offset -= 16;
                        if (pattern[offset] && *depth != 0) pixels[i] = (unsigned short)color;
                        if (delta > 0) {
                            pixels = (unsigned short *)((unsigned char *)pixels + pitch);
                            depth += depth_stride;
                            depth = (unsigned short *)ZBufferPtr->Wrap_Overflow((unsigned int)depth);
                            delta -= dx2;
                        }
                        delta += dy2;
                        if (depth_stride > 0) {
                            depth++;
                            depth = (unsigned short *)ZBufferPtr->Wrap_Overflow((unsigned int)depth);
                        } else {
                            depth++;
                            depth = (unsigned short *)ZBufferPtr->Wrap_Underflow((unsigned int)depth);
                        }
                    }
                } else {
                    int delta = dx2 - dy;
                    int k = 0;
                    for (int i = 0; i < dy; i++, offset += pattern_step) {
                        if (offset < 0) offset += 16;
                        if (offset >= 16) offset -= 16;
                        if (pattern[offset] && *depth != 0) pixels[k] = (unsigned short)color;
                        if (delta > 0) {
                            k++;
                            depth++;
                            depth = (unsigned short *)ZBufferPtr->Wrap_Overflow((unsigned int)depth);
                            delta -= dy2;
                        }
                        delta += dx2;
                        pixels = (unsigned short *)((unsigned char *)pixels + pitch);
                        if (depth_stride > 0) {
                            depth += depth_stride;
                            depth = (unsigned short *)ZBufferPtr->Wrap_Overflow((unsigned int)depth);
                        } else {
                            depth += depth_stride;
                            depth = (unsigned short *)ZBufferPtr->Wrap_Underflow((unsigned int)depth);
                        }
                    }
                }
            }
        }
        Unlock();
        return offset;
    }
    return offset;
}
