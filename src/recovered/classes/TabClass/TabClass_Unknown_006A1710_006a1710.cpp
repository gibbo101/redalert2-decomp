// void TabClass::Unknown_006A1710() (0x006A1710)
// Draws the bar's background shape at the origin of the sidebar surface
// (brightness 1000) and notes that a sidebar button repainted.
#include "shared/tab.hpp"
// @ref ?unknown_surface_839948@@3PAVSurface@@A=00839948
// @ref ?unknown_drawer_8323cc@@3PAVConvertClass@@A=008323cc
// @ref ?unknown_buffer_ac10f8@@3PAXA=00ac10f8
// @ref ?unknown_flag_abcd84@@3_NA=00abcd84
// @ref ?CC_Draw_Shape@@YIXPAVSurface@@PAVConvertClass@@PBUShapeFileStruct@@HABUPoint2D@@ABVRect@@HHHHHHHU4@@Z=0049eea0

void TabClass::Unknown_006A1710()
{
    ShapeFileStruct const *shape = (ShapeFileStruct const *)unknown_buffer_ac10f8;
    CC_Draw_Shape(unknown_surface_839948, unknown_drawer_8323cc, shape, 0,
                  Point2D(0, 0), unknown_surface_839948->Get_Rect(), 0, 0, 0, 0, 1000, 0, 0, Point2D(0, 0));
    unknown_flag_abcd84 = true;
}
