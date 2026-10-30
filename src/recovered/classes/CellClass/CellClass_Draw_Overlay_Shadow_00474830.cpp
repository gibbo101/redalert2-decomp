// void CellClass::unknown_474830(Point2D const &point, Rect const &clip) (0x00474830):
// Westwood's Draw_Overlay_Shadow: the overlay's shadow frame (the second half of
// its frames; frame 0 for a crate), or a rubble building's shadow, through the
// cell's drawer.
#include "shared/cell.hpp"
#include "shared/unknown_static_rect.hpp"
#define SHAPE_FILE_EMPTY_RECT unknown_static_rect
#include "shared/shape_file.hpp"
#include "shared/overlay_type.hpp"
#include "shared/building_type_class.hpp"
#include "shared/light_convert.hpp"
#include "shared/palette.hpp"
#include "shared/unknown_globals.hpp"
// @ref ?Init_Drawer@CellClass@@QAEXPAVLightConvertClass@@HHHHH@Z=004790f0
// @ref ?unknown_surface_83995c@@3PAVSurface@@A=0083995c
// @ref ?CC_Draw_Shape@@YIXPAVSurface@@PAVConvertClass@@PBUShapeFileStruct@@HABUPoint2D@@ABVRect@@HHHHHHHU4@@Z=0049eea0
void CellClass::unknown_474830(Point2D const &xpoint, Rect const &clip)
{
    int yoffset = unknown_11b * 15;
    OverlayTypeClass *overlay = OverlayTypes[OverlayIndex];
    ShapeFileStruct *shape = (ShapeFileStruct *)overlay->unknown_slot39();
    Point2D point = xpoint + unknown_475440();
    point -= Point2D(clip.X, clip.Y);
    if (unknown_140 & 0x80) {
        if (OverlayData >= 9 && OverlayData <= 17) {
            point.X -= 15;
            point.Y += 7;
        }
    }
    if (unknown_34 == 0) {
        Init_Drawer(0, 0x10000, 0, 1000, 1000, 1000);
    }
    unsigned char frame = OverlayData;
    if (overlay->Crate) {
        frame = 0;
    } else if (overlay->IsRubble) {
        if (unknown_40 != 0) {
            ShapeFileStruct *image;
            int rubble;
            if (((BuildingTypeClass *)unknown_40)->unknown_func_458e50((void **)&image, &rubble)) {
                CC_Draw_Shape(unknown_surface_83995c, unknown_34, image, rubble, point, clip, 0x4601, 0, -2 - yoffset, 0, 1000, 0, 0, Point2D(0, 0));
            }
        }
        return;
    }
    CC_Draw_Shape(unknown_surface_83995c, unknown_34, shape, frame + shape->FrameCount / 2, point, clip, 0x4601, 0, -2 - yoffset, 0, 1000, 0, 0, Point2D(0, 0));
}
