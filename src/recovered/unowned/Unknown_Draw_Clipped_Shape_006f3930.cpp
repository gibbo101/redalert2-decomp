// void __fastcall Unknown_006F3930(Surface *surface, Rect const &window, ConvertClass *drawer,
//                                  ShapeFileStruct const *shape640, ShapeFileStruct const *shape) -- 0x006F3930
// Draws one of two shapes (by whether the screen width at 0x008523E0 is 640) at the point
// stored at 0x00AC11C0, clipped to the window with the part beyond 800 x 600 halved
// (hypothesis).
#include "shared/rect.hpp"
// @ref ?CC_Draw_Shape@@YIXPAVSurface@@PAVConvertClass@@PBUShapeFileStruct@@HABUPoint2D@@ABVRect@@HHHHHHHUPoint2D@@@Z=0049eea0
// @ref ?unknown_point_ac11c0@@3PAUPoint2D@@A=00ac11c0
// @ref ?unknown_value_8523e0@@3HA=008523e0
class Surface;
class ConvertClass;
struct ShapeFileStruct;
void __fastcall CC_Draw_Shape(Surface *surface, ConvertClass *drawer, ShapeFileStruct const *shape, int frame,
                              Point2D const &point, Rect const &window, int flags, int unknown8,
                              int unknown9, int unknown10, int brightness, int unknown12,
                              int unknown13, Point2D offset);   // 0x0049EEA0
extern Point2D *unknown_point_ac11c0;
extern int unknown_value_8523e0;

void __fastcall Unknown_006F3930(Surface *surface, Rect const &window, ConvertClass *drawer, ShapeFileStruct const *shape640, ShapeFileStruct const *shape)
{
    Point2D point(0, 0);
    Rect clip(window.X, window.Y, window.Width, window.Height);
    if (clip.Width > 800) {
        clip.Width = (clip.Width - 800) / 2 + 800;
    }
    if (clip.Height > 600) {
        clip.Height = (clip.Height - 600) / 2 + 600;
    }
    point.X = unknown_point_ac11c0->X;
    point.Y = unknown_point_ac11c0->Y;
    if (unknown_value_8523e0 == 0x280) {
        CC_Draw_Shape(surface, drawer, shape640, 0, point, clip, 0x400, 0, 0, 0, 1000, 0, 0, Point2D(0, 0));
    } else {
        CC_Draw_Shape(surface, drawer, shape, 0, point, clip, 0x400, 0, 0, 0, 1000, 0, 0, Point2D(0, 0));
    }
}
