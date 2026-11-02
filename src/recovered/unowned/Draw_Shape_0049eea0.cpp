#define SHAPE_FILE_EMPTY_RECT draw_cliprect
#include "shared/palette.hpp"
#include "shared/surface.hpp"
#include "shared/blit.hpp"

void __fastcall CC_Draw_Shape(Surface *destination, ConvertClass *convert, ShapeFileStruct const *file, int frame,
                              Point2D const &point, Rect const &window, int flags, int remap_bits,
                              int height_offset, int gradient, int intensity, int depth_file_bits,
                              int depth_frame, Point2D depth_offset)
{
    if (!file) return;
    convert->ActiveRemap = reinterpret_cast<unsigned char const *>(remap_bits);
    int x = point.X;
    int y = point.Y;
    Rect area = file->Get_Frame_Rect(frame);
    void const *pixels = file->Get_Frame_Data(frame);
    int width = file->Get_Width();
    int height = file->Get_Height();
    BSurface shape(area.Width, area.Height, 1, const_cast<void *>(pixels));
    Point2D depth_point = depth_offset;
    BSurface *depth_shape;
    Rect depth_area;
    ShapeFileStruct const *depth_file = reinterpret_cast<ShapeFileStruct const *>(depth_file_bits);
    if (depth_file) {
        depth_area = depth_file->Get_Frame_Rect(depth_frame);
        depth_shape = new BSurface(depth_area.Width, depth_area.Height, 1,
                                  const_cast<void *>(depth_file->Get_Frame_Data(depth_frame)));
    } else {
        depth_shape = 0;
        depth_area = draw_cliprect;
    }
    if (flags & 0x200) {
        x -= width / 2;
        y -= height / 2;
    }
    if (depth_file) {
        depth_point -= Point2D(width, height) / 2 - Point2D(area.X, area.Y);
    }
    x += area.X;
    y += area.Y;
    area.X = 0;
    area.Y = 0;
    if (depth_file) {
        depth_point.X += depth_area.X;
        depth_point.Y += depth_area.Y;
        area = area.Intersect(Rect(-depth_point.X, -depth_point.Y, depth_area.Width, depth_area.Height));
        if (area.Width <= 0 || area.Height <= 0) goto cleanup;
    }
    if (remap_bits) flags |= 0x10;
    {
        if (file->Is_RLE_Compressed(frame)) {
            RLEBlitter const *blitter = convert->RLEBlitter_From_Flags_00485d60(flags);
            if (blitter) RLE_Blit(*destination, window, Rect(x, y, area.Width, area.Height), shape, area, area,
                                  *blitter, height_offset, gradient, intensity, 0,
                                  reinterpret_cast<int>(depth_shape), BlitPair(depth_point.X, depth_point.Y));
        } else {
            Blitter const *blitter = convert->Select_Blitter_00485AA0(flags);
            if (blitter) Bit_Blit(*destination, window, Rect(x, y, area.Width, area.Height), shape,
                                  shape.Get_Rect(), area, *blitter, height_offset, gradient, intensity, 0);
        }
    }
cleanup:
    if (depth_shape) delete depth_shape;
}
