// Windowed pixel-run blit, full original00434B40..00435057.
#include "shared/blit.hpp"
// @ref ?ZBufferPtr@@3PAVZBuffer@@A=008315b4
// @ref ?ABufferPtr@@3PAVABuffer@@A=00839c6c
// @ref ?BlitRamps@@3PAUBlitRamp@@A=007ce168
// Native839C6C carries the interpolated depth values; names of buffer classes remain hypotheses.
bool __fastcall Bit_Blit(Surface &dest, Rect const &destwindow, Rect const &destarea,
    Surface &source, Rect const &sourcewindow, Rect const &sourcearea,
    Blitter const &blitter, int depth, int ramp_index, int alpha, int unknown)
{
    Rect src = sourcearea;
    Rect dst = destarea;
    bool overlap = false;
    void *dest_pixels = 0;
    void *source_pixels = 0;
    unsigned int depth_pointer = 0;
    unsigned int alpha_pointer = 0;
    int depth_level = 0;
    int depth_pitch = 0;
    int alpha_pitch = 0;
    int fraction = 0;
    int increment = 0;
    int limit = 0;
    int ratio = 0;
    BlitRamp *ramp = &BlitRamps[ramp_index];
    if (!Prep_For_Blit(dest, destwindow, dst, source, sourcewindow, src, overlap, dest_pixels, source_pixels)) return false;
    if (ZBufferPtr) {
        Point2D point;
        point = destwindow.Top_Left() + dst.Top_Left();
        point.Y -= ZBufferPtr->Area.Y;
        alpha_pointer = (unsigned int)ZBufferPtr->Get_Buffer_Ptr(point);
    }
    if (ABufferPtr) {
        Point2D point;
        point = destwindow.Top_Left() + dst.Top_Left();
        point.Y -= ABufferPtr->Area.Y;
        depth_pointer = (unsigned int)ABufferPtr->Get_Buffer_Ptr(point);
        fraction = 0;
        increment = ramp->Numerator;
        limit = ramp->Denominator;
        ratio = limit / increment;
        if (ramp->Flag) {
            depth_level = (unsigned short)ABufferPtr->Get_Scroll_Delta(destwindow.Y + dst.Y - ABufferPtr->Area.Y);
            depth_level += depth;
            depth_level = (depth_level / ramp->Divisor) * ramp->Divisor;
        } else {
            depth_level = (unsigned short)ABufferPtr->Get_Scroll_Delta(destwindow.Y + dst.Y + dst.Height - 1 - ABufferPtr->Area.Y);
            depth_level += depth;
            depth_level = (depth_level / ratio) * ratio;
            depth_level -= dst.Height / ratio;
            fraction = limit - dst.Height % ratio;
            if (fraction == limit) {
                fraction = 0;
                depth_level += ramp->Step;
            }
        }
    }
    if (dst.Width * dest.Bytes_Per_Pixel() == dest.Stride() && dest.Stride() == source.Stride()) {
        int count = src.Height * src.Width < dst.Height * dst.Width ? src.Height * src.Width : dst.Height * dst.Width;
        if (overlap) blitter.BlitBackward(dest_pixels, source_pixels, count, 0, 0, 0, 1000);
        else blitter.BlitForward(dest_pixels, source_pixels, count, 0, 0, 0, 1000, 0);
    } else {
        int source_pitch = source.Stride();
        int dest_pitch = dest.Stride();
        if (ABufferPtr) depth_pitch = ABufferPtr->Width;
        if (ZBufferPtr) alpha_pitch = ZBufferPtr->Width;
        if (overlap) {
            source_pitch = -source_pitch;
            dest_pitch = -dest_pitch;
            depth_pitch = -depth_pitch;
            alpha_pitch = -alpha_pitch;
            source_pixels = (char *)source_pixels + (src.Height - 1) * source.Stride();
            dest_pixels = (char *)dest_pixels + (dst.Height - 1) * dest.Stride();
            if (ABufferPtr) {
                depth_pointer = ABufferPtr->Wrap_Overflow(depth_pointer + 2 * src.Height - 2 * ABufferPtr->Width);
                depth_level -= src.Height - 1;
            }
            if (ZBufferPtr) alpha_pointer = ZBufferPtr->Wrap_Overflow(alpha_pointer + 2 * src.Height - 2 * ZBufferPtr->Width);
        }
        int rows = src.Height < dst.Height ? src.Height : dst.Height;
        if (overlap) {
            for (int row = 0; row < rows; ++row) {
                blitter.BlitBackward(dest_pixels, source_pixels, src.Width, depth_level, (int)depth_pointer, (int)alpha_pointer, alpha);
                dest_pixels = (char *)dest_pixels + dest_pitch;
                source_pixels = (char *)source_pixels + source_pitch;
                if (ABufferPtr) {
                    depth_pointer += 2 * depth_pitch;
                    depth_pointer = ABufferPtr->Wrap_Underflow(depth_pointer);
                    fraction += increment;
                    if (fraction >= limit) {
                        depth_level += ramp->Step;
                        fraction -= limit;
                    }
                }
                if (ZBufferPtr) {
                    alpha_pointer += 2 * alpha_pitch;
                    alpha_pointer = ZBufferPtr->Wrap_Underflow(alpha_pointer);
                }
            }
        } else {
            for (int row = 0; row < rows; ++row) {
                blitter.BlitForward(dest_pixels, source_pixels, src.Width, depth_level, (int)depth_pointer, (int)alpha_pointer, alpha, 0);
                dest_pixels = (char *)dest_pixels + dest_pitch;
                source_pixels = (char *)source_pixels + source_pitch;
                if (ABufferPtr) {
                    depth_pointer += 2 * depth_pitch;
                    depth_pointer = ABufferPtr->Wrap_Overflow(depth_pointer);
                    fraction += increment;
                    if (fraction >= limit) {
                        depth_level += ramp->Step;
                        fraction -= limit;
                    }
                }
                if (ZBufferPtr) {
                    alpha_pointer += 2 * alpha_pitch;
                    alpha_pointer = ZBufferPtr->Wrap_Overflow(alpha_pointer);
                }
            }
        }
    }
    dest.Unlock();
    source.Unlock();
    return true;
}
