// Draw a clipped 16-bit line, plotting only where the depth buffer value is
// zero (empty_only) or only where it is not; the depth pointer walks the
// ZBuffer ring alongside the pixel pointer.
#include "shared/blit.hpp"
#include "shared/crt_memory.hpp"
#include "shared/dsurface.hpp"
// @ref ?Clip_Line@@YI_NAAUPoint2D@@0ABVRect@@@Z=00775620
// @ref ?Get_Buffer_Ptr@ZBuffer@@QAEPAGUPoint2D@@@Z=00411230
// @ref ?ZBufferPtr@@3PAVZBuffer@@A=008315b4

bool DSurface::Draw_Line_Depth_Masked(Point2D const &startpoint, Point2D const &endpoint, int color, bool empty_only)
{
    if (Bytes_Per_Pixel() == 2) {
        Rect clip = Get_Rect();
        Point2D start = Offset_Point(startpoint, clip);
        Point2D end = Offset_Point(endpoint, clip);
        if (Clip_Line(start, end, clip)) {
            if (start.X > end.X) {
                Point2D temp = start;
                start = end;
                end = temp;
            }
            Point2D position = start;
            position.Y -= ZBufferPtr->Area.Y;
            unsigned short *depth = ZBufferPtr->Get_Buffer_Ptr(position);
            int depth_stride = ZBufferPtr->Width;
            if (start.Y > end.Y) depth_stride = -depth_stride;
            unsigned short *pixels = (unsigned short *)Lock(start);
            if (pixels) {
            if (empty_only) {
                if (start.Y == end.Y) {
                    for (int index = 0; index <= end.X - start.X; ++index) {
                        if (*depth == 0) pixels[index] = (unsigned short)color;
                        ZBufferPtr->Advance_Pointer(depth, 1, depth_stride);
                    }
                } else if (start.X == end.X) {
                    int stride;
                    if (start.Y > end.Y) stride = -Stride();
                    else stride = Stride();
                    int height = abs(end.Y - start.Y);
                    for (int index = 0; index <= height; ++index) {
                        if (*depth == 0) *pixels = (unsigned short)color;
                        ZBufferPtr->Advance_Pointer(depth, depth_stride, depth_stride);
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
                        for (int index = 0; index < dx; ++index) {
                            if (*depth == 0) pixels[index] = (unsigned short)color;
                            if (error > 0) {
                                pixels = (unsigned short *)((char *)pixels + stride);
                                depth = ZBufferPtr->Wrap_Pointer(depth + depth_stride);
                                error -= dx2;
                            }
                            ZBufferPtr->Advance_Pointer(depth, 1, depth_stride);
                            error += dy2;
                        }
                    } else {
                        int error = dx2 - dy;
                        int offset = 0;
                        for (int count = dy; count > 0; --count) {
                            if (*depth == 0) pixels[offset] = (unsigned short)color;
                            if (error > 0) {
                                error -= dy2;
                                ++offset;
                                depth = ZBufferPtr->Wrap_Pointer(depth + 1);
                            }
                            error += dx2;
                            pixels = (unsigned short *)((char *)pixels + stride);
                            ZBufferPtr->Advance_Pointer(depth, depth_stride, depth_stride);
                        }
                    }
                }
            } else {
                if (start.Y == end.Y) {
                    for (int index = 0; index <= end.X - start.X; ++index) {
                        if (*depth != 0) pixels[index] = (unsigned short)color;
                        ZBufferPtr->Advance_Pointer(depth, 1, depth_stride);
                    }
                } else if (start.X == end.X) {
                    int stride;
                    if (start.Y > end.Y) stride = -Stride();
                    else stride = Stride();
                    int height = abs(end.Y - start.Y);
                    for (int index = 0; index <= height; ++index) {
                        if (*depth != 0) *pixels = (unsigned short)color;
                        ZBufferPtr->Advance_Pointer(depth, depth_stride, depth_stride);
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
                        for (int index = 0; index < dx; ++index) {
                            if (*depth != 0) pixels[index] = (unsigned short)color;
                            if (error > 0) {
                                pixels = (unsigned short *)((char *)pixels + stride);
                                depth = ZBufferPtr->Wrap_Pointer(depth + depth_stride);
                                error -= dx2;
                            }
                            ZBufferPtr->Advance_Pointer(depth, 1, depth_stride);
                            error += dy2;
                        }
                    } else {
                        int error = dx2 - dy;
                        int offset = 0;
                        for (int count = dy; count > 0; --count) {
                            if (*depth != 0) pixels[offset] = (unsigned short)color;
                            if (error > 0) {
                                error -= dy2;
                                ++offset;
                                depth = ZBufferPtr->Wrap_Pointer(depth + 1);
                            }
                            error += dx2;
                            pixels = (unsigned short *)((char *)pixels + stride);
                            ZBufferPtr->Advance_Pointer(depth, depth_stride, depth_stride);
                        }
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
