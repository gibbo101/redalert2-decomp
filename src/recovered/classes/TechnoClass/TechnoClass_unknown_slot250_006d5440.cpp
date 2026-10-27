// void TechnoClass::unknown_slot250(Point2D const &point, Rect const &window) (0x006D5440)
// Draws the rank pip (PIPS.SHP frame 13, 14 or 18 by the +0x118 ranks)
// near point; infantry use a smaller offset.
#include "shared/techno.hpp"
#include "shared/object_type.hpp"
#include "shared/palette.hpp"
#include "shared/gadget.hpp"
#include "shared/gscreen.hpp"
// @ref ?unknown_pips_shapes_a72fe4@@3PBXB=00a72fe4
// @ref ?unknown_713400@UnknownTechnoPair@@QBE_NXZ=00713400
// @ref ?unknown_drawer_8323c4@@3PAVConvertClass@@A=008323c4
// @ref ?unknown_surface_83995c@@3PAVSurface@@A=0083995c
// @ref ?CC_Draw_Shape@@YIXPAVSurface@@PAVConvertClass@@PBUShapeFileStruct@@HABUPoint2D@@ABVRect@@HHHHHHHU4@@Z=0049eea0

void TechnoClass::unknown_slot250(Point2D const &point, Rect const &window)
{
    ObjectTypeClass *type = Class_Of();
    void const *pips = unknown_pips_shapes_a72fe4;
    int frame = -1;
    if (unknown_118.unknown_7133a0()) {
        frame = 13;
    }
    if (unknown_118.unknown_713420()) {
        frame = 14;
    }
    if (unknown_118.unknown_713400()) {
        frame = 18;
    }
    if (frame != -1) {
        Point2D position = Point2D(point.X + 5, point.Y + 2);
        if (Kind_Of() != 15) {
            position.X += 5;
            position.Y += 4;
        }
        CC_Draw_Shape(unknown_surface_83995c, unknown_drawer_8323c4, (ShapeFileStruct const *)pips, frame, position, window,
                      0xE00, 0, -2, 0, 1000, 0, 0, Point2D(0, 0));
    }
}
