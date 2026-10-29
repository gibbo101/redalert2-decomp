// void TerrainClass::unknown_slot67(int arg1, int arg2) (0x006E3990, slot 67)
// Draws the terrain object (hypothesis: Draw_It) at the screen point arg1
// within the window arg2: the frame follows the animation stage (crumbling
// objects offset by their +0xB5 flag; a damaged static object shows frame
// 1), lifted by its height. Tiberium spawners draw with the 0x008323BC
// drawer 16 pixels higher; the shadow (second half of the frames) follows
// when shadows are on (0x007D88D5).
#include "shared/terrain.hpp"
#include "shared/tactical.hpp"
#include "shared/unknown_static_rect.hpp"
#define SHAPE_FILE_EMPTY_RECT unknown_static_rect
#include "shared/palette.hpp"
// @ref ?Unknown_006A2970@@YIHH@Z=006a2970
// @ref ?Unknown_004790F0@CellClass@@QAEXHHHHHH@Z=004790f0
// @ref ?unknown_drawer_8323bc@@3PAVConvertClass@@A=008323bc
// @ref ?unknown_surface_83995c@@3PAVSurface@@A=0083995c
// @ref ?unknown_flag_7d88d5@@3_NA=007d88d5
// @ref ?CC_Draw_Shape@@YIXPAVSurface@@PAVConvertClass@@PBUShapeFileStruct@@HABUPoint2D@@ABVRect@@HHHHHHHU4@@Z=0049eea0


// The object is animated or crumbling (local helper; slot 67's shadow flags).
static inline bool Is_Animating(TerrainClass const *terrain)
{
    return terrain->Class->IsAnimated || terrain->unknown_b5;
}

void TerrainClass::unknown_slot67(int arg1, int arg2)
{
    Point2D const *point = (Point2D const *)arg1;
    Rect const *window = (Rect const *)arg2;
    Cell where = unknown_slot104();
    CellClass &cell = Map_Cell(where);
    ShapeFileStruct const *shape = (ShapeFileStruct const *)unknown_slot26();
    if (shape != 0) {
        int frame = 0;
        if (Class->IsAnimated) {
            frame = Animation.Value;
        } else if (unknown_b5) {
            frame = Animation.Value + unknown_b5;
        } else if (Strength < 2) {
            frame = 1;
        }
        Point2D position = *point;
        int height = -Unknown_006A2970(unknown_slot110());
        if (cell.unknown_34 == 0) {
            cell.Unknown_004790F0(0, 0x10000, 0, 1000, 1000, 1000);
        }
        ConvertClass *drawer;
        int brightness;
        if (Class->SpawnsTiberium) {
            drawer = unknown_drawer_8323bc;
            brightness = cell.unknown_10a;
            position -= Point2D(0, 16);
        } else {
            drawer = (ConvertClass *)cell.unknown_34;
            brightness = cell.unknown_10c;
        }
        int flags;
        if (Is_Animating(this)) {
            flags = 0x2E00;
        } else {
            flags = 0x4E00;
        }
        CC_Draw_Shape(unknown_surface_83995c, drawer, shape, frame, position, *window, flags, 0, height - 12, 2, brightness, 0, 0, Point2D(0, 0));
        if (unknown_flag_7d88d5) {
            CC_Draw_Shape(unknown_surface_83995c, (ConvertClass *)cell.unknown_34, shape, shape->FrameCount / 2 + frame, position, *window, flags | 1, 0, height - 3, 0, 1000, 0, 0, Point2D(0, 0));
        }
    }
}
