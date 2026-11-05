// Compressed scanline blit, native004350C0..00435530 plus15 frozenNOP.
#include "shared/blit.hpp"
#include "shared/rle_blitter.hpp"
extern unsigned char Blit_RLE_Default_Depth[];
// @ref ?Blit_RLE_Default_Depth@@3PAEA=0084ea78
// @ref ?ZBufferPtr@@3PAVZBuffer@@A=008315b4
// @ref ?ABufferPtr@@3PAVABuffer@@A=00839c6c
// @ref ?BlitRamps@@3PAUBlitRamp@@A=007ce168
bool __fastcall RLE_Blit(Surface &dest, Rect const &destwindow, Rect const &destarea,
    Surface &source, Rect const &sourcewindow, Rect const &sourcearea,
    RLEBlitter const &blitter, int depth, int ramp_index, int alpha, int unknown,
    int depth_shape_address, BlitPair depth_point)
{
    unsigned int depth_pointer = 0;
    unsigned int alpha_pointer = 0;
    char *shape_pixels = 0;
    int depth_pitch = 0;
    int alpha_pitch = 0;
    int depth_level = 0;
    Rect src = sourcearea;
    Rect dst = destarea;
    Rect shape_area;
    int fraction = 0;
    int increment = 0;
    int limit = 0;
    int ratio = 0;
    int shape_width = 0;
    BlitRamp *ramp = &BlitRamps[ramp_index];
    Surface *depth_shape = (Surface *)depth_shape_address;
    if (!Clip_Blit_Rects(dst, destwindow, src, sourcewindow)) return false;
    int left = src.X - sourcewindow.X;
    int top = src.Y - sourcewindow.Y;
    void *dest_pixels = dest.Lock(destwindow.Top_Left() + dst.Top_Left());
    if (!dest_pixels) return false;
    if (ABufferPtr) {
        Point2D point;
        point = destwindow.Top_Left() + dst.Top_Left();
        point.Y -= ABufferPtr->Area.Y;
        depth_pointer = (unsigned int)ABufferPtr->Get_Buffer_Ptr(point);
        depth_pitch = ABufferPtr->Width;
        fraction = 0;
        increment = ramp->Numerator;
        limit = ramp->Denominator;
        ratio = limit / increment;
        if (ramp->Flag) {
            depth_level = (unsigned short)ABufferPtr->Get_Scroll_Delta(point.Y);
            depth_level += depth;
            depth_level = (depth_level / ramp->Divisor) * ramp->Divisor;
        } else {
            depth_level = (unsigned short)ABufferPtr->Get_Scroll_Delta(destwindow.Y + destarea.Y + destarea.Height - 1 - ABufferPtr->Area.Y);
            depth_level += depth;
            if (!depth_shape) {
                depth_level = (depth_level / ratio) * ratio;
                int lines = destarea.Y + destarea.Height - dst.Y;
                depth_level -= lines / ratio;
                fraction = limit - lines % ratio;
                if (fraction == limit) {
                    fraction = 0;
                    depth_level += ramp->Step;
                }
            }
        }
        if (depth_shape) {
            shape_area = depth_shape->Get_Rect();
            shape_width = shape_area.Width;
            shape_pixels = (char *)depth_shape->Lock(Point2D(shape_area.X, shape_area.Y) + Point2D(depth_point.X, depth_point.Y) + Point2D(left, top));
        } else shape_pixels = (char *)Blit_RLE_Default_Depth;
    }
    if (ZBufferPtr) {
        Point2D point;
        point = destwindow.Top_Left() + dst.Top_Left();
        point.Y -= ZBufferPtr->Area.Y;
        alpha_pointer = (unsigned int)ZBufferPtr->Get_Buffer_Ptr(point);
        alpha_pitch = ZBufferPtr->Width;
    }
    void *source_pixels = source.Lock();
    if (!source_pixels) {
        dest.Unlock();
        return false;
    }
    while (top > 0) {
        source_pixels = (unsigned char *)source_pixels + *(unsigned short *)source_pixels;
        --top;
    }
    int dest_pitch = dest.Stride();
    int rows = src.Height < dst.Height ? src.Height : dst.Height;
    for (int row = 0; row < rows; ++row) {
        blitter.Blit(dest_pixels, (unsigned short *)source_pixels + 1, src.Width, left,
            depth_level, (int)depth_pointer, (int)alpha_pointer, alpha, 0, (int)shape_pixels);
        source_pixels = (unsigned char *)source_pixels + *(unsigned short *)source_pixels;
        dest_pixels = (char *)dest_pixels + dest_pitch;
        if (ABufferPtr) {
            depth_pointer += 2 * depth_pitch;
            depth_pointer = ABufferPtr->Wrap_Overflow(depth_pointer);
            if (depth_shape) shape_pixels += shape_width;
            else {
                fraction += increment;
                if (fraction >= limit) {
                    depth_level += ramp->Step;
                    fraction -= limit;
                }
            }
            alpha_pointer += 2 * alpha_pitch;
            alpha_pointer = ZBufferPtr->Wrap_Overflow(alpha_pointer);
        }
    }
    dest.Unlock();
    source.Unlock();
    return true;
}
