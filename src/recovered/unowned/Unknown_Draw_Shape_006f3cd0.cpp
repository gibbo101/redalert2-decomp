// void __fastcall Unknown_6F3CD0(Surface *surface, Rect const &window) -- 0x6F3CD0
// Runs 0x006F34D0 and 0x006F3650 then draws the backdrop shape (hypothesis).
#include "shared/rect.hpp"
// @ref ?CC_Draw_Shape@@YIXPAVSurface@@PAVConvertClass@@PBUShapeFileStruct@@HABUPoint2D@@ABVRect@@HHHHHHHUPoint2D@@@Z=0049eea0
// @ref ?Unknown_006F34D0@@YIXPAVSurface@@ABVRect@@@Z=006f34d0
// @ref ?Unknown_006F3650@@YIXPAVSurface@@ABVRect@@_N@Z=006f3650
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
void __fastcall Unknown_006F34D0(Surface *surface, Rect const &window);
void __fastcall Unknown_006F3650(Surface *surface, Rect const &window, bool arg3);
extern Point2D *unknown_point_ac11c0;
extern ConvertClass *unknown_drawer_ac1170;
extern ShapeFileStruct *unknown_shape_ac1104;

void __fastcall Unknown_6F3CD0(Surface *surface, Rect const &window)
{
    Unknown_006F34D0(surface, window);
    Unknown_006F3650(surface, window, false);
    Point2D point(0, 0);
    point.X = unknown_point_ac11c0->X;
    point.Y = unknown_point_ac11c0->Y;
    CC_Draw_Shape(surface, unknown_drawer_ac1170, unknown_shape_ac1104, 0, point, window, 0x400, 0, 0, 0, 1000, 0, 0, Point2D(0, 0));
}
