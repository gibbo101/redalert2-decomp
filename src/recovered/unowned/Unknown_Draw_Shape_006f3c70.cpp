// void __fastcall Unknown_6F3C70(Surface *surface, Rect const &window) -- 0x6F3C70
// Draws the backdrop shape at 0x00AC1104 (hypothesis).
#include "shared/rect.hpp"
// @ref ?CC_Draw_Shape@@YIXPAVSurface@@PAVConvertClass@@PBUShapeFileStruct@@HABUPoint2D@@ABVRect@@HHHHHHHUPoint2D@@@Z=0049eea0
// @ref ?unknown_point_ac11c0@@3PAUPoint2D@@A=00ac11c0
// @ref ?unknown_drawer_ac1170@@3PAVConvertClass@@A=00ac1170
// @ref ?unknown_shape_ac1104@@3PAUShapeFileStruct@@A=00ac1104

class Surface;
class ConvertClass;
struct ShapeFileStruct;
void __fastcall CC_Draw_Shape(Surface *surface, ConvertClass *drawer, ShapeFileStruct const *shape, int frame,
                              Point2D const &point, Rect const &window, int flags, int unknown8,
                              int unknown9, int unknown10, int brightness, int unknown12,
                              int unknown13, Point2D offset);   // 0x0049EEA0
extern Point2D *unknown_point_ac11c0;
extern ConvertClass *unknown_drawer_ac1170;
extern ShapeFileStruct *unknown_shape_ac1104;

void __fastcall Unknown_6F3C70(Surface *surface, Rect const &window)
{
    Point2D point(0, 0);
    point.X = unknown_point_ac11c0->X;
    point.Y = unknown_point_ac11c0->Y;
    CC_Draw_Shape(surface, unknown_drawer_ac1170, unknown_shape_ac1104, 0, point, window, 0x400, 0, 0, 0, 1000, 0, 0, Point2D(0, 0));
}
