// void __fastcall Unknown_006F3650(Surface *surface, Rect const &window, bool arg3) -- 0x006F3650
// Loads the interface art once, then draws the panel frame shapes clipped to the window (hypothesis).
#include "shared/rect.hpp"
// @ref ?CC_Draw_Shape@@YIXPAVSurface@@PAVConvertClass@@PBUShapeFileStruct@@HABUPoint2D@@ABVRect@@HHHHHHHUPoint2D@@@Z=0049eea0
// @ref ?Unknown_0051A2B0@@YIXXZ=0051a2b0
// @ref ?Unknown_006F3D50@@YIXXZ=006f3d50
// @ref ?unknown_load_art_6f1fa0@@YIXPBDPAPAX1@Z=006f1fa0
// @ref ?Unknown_006F3E70@@YIXHH@Z=006f3e70
// @ref ?Unknown_006F34D0@@YIXPAVSurface@@ABVRect@@@Z=006f34d0
// @ref ?unknown_flag_ac119c@@3_NA=00ac119c
// @ref ?unknown_value_8523e0@@3HA=008523e0
// @ref ?unknown_value_8523e4@@3HA=008523e4
// @ref ?unknown_count_ac102c@@3HA=00ac102c
// @ref ?unknown_name_7f871c@@3QBDB=007f871c
// @ref ?unknown_art_ac1184@@3PAXA=00ac1184
// @ref ?unknown_art_ac1188@@3PAXA=00ac1188
// @ref ?unknown_name_7f8720@@3QBDB=007f8720
// @ref ?unknown_art_ac118c@@3PAXA=00ac118c
// @ref ?unknown_art_ac1190@@3PAXA=00ac1190
// @ref ?unknown_name_7f8724@@3QBDB=007f8724
// @ref ?unknown_art_ac1194@@3PAXA=00ac1194
// @ref ?unknown_art_ac1198@@3PAXA=00ac1198
// @ref ?unknown_rect_ac11c4@@3PAVRect@@A=00ac11c4
// @ref ?unknown_rect_ac11c8@@3PAVRect@@A=00ac11c8
// @ref ?unknown_rect_ac11b4@@3PAVRect@@A=00ac11b4
// @ref ?unknown_rect_ac11cc@@3PAVRect@@A=00ac11cc
// @ref ?unknown_rect_ac11d0@@3PAVRect@@A=00ac11d0
// @ref ?unknown_shape_ac10e8@@3PAUShapeFileStruct@@A=00ac10e8
// @ref ?unknown_shape_ac107c@@3PAUShapeFileStruct@@A=00ac107c
// @ref ?unknown_shape_ac10b8@@3PAUShapeFileStruct@@A=00ac10b8
// @ref ?unknown_shape_ac1044@@3PAUShapeFileStruct@@A=00ac1044
// @ref ?unknown_shape_ac10d8@@3PAUShapeFileStruct@@A=00ac10d8
// @ref ?unknown_shape_ac1060@@3PAUShapeFileStruct@@A=00ac1060
// @ref ?unknown_drawer_ac1188@@3PAVConvertClass@@A=00ac1188
// @ref ?unknown_drawer_ac1190@@3PAVConvertClass@@A=00ac1190
// @ref ?unknown_drawer_ac1198@@3PAVConvertClass@@A=00ac1198

class Surface;
class ConvertClass;
struct ShapeFileStruct;
void __fastcall CC_Draw_Shape(Surface *surface, ConvertClass *drawer, ShapeFileStruct const *shape, int frame,
                              Point2D const &point, Rect const &window, int flags, int unknown8,
                              int unknown9, int unknown10, int brightness, int unknown12,
                              int unknown13, Point2D offset);   // 0x0049EEA0
void __fastcall Unknown_0051A2B0();
void __fastcall Unknown_006F3D50();
void __fastcall unknown_load_art_6f1fa0(char const *name, void **shape, void **data);   // 0x006F1FA0
void __fastcall Unknown_006F3E70(int arg1, int arg2);
void __fastcall Unknown_006F34D0(Surface *surface, Rect const &window);
extern bool unknown_flag_ac119c;
extern int unknown_value_8523e0;
extern int unknown_value_8523e4;
extern int unknown_count_ac102c;
extern char const * const unknown_name_7f871c;
extern void *unknown_art_ac1184;
extern void *unknown_art_ac1188;
extern char const * const unknown_name_7f8720;
extern void *unknown_art_ac118c;
extern void *unknown_art_ac1190;
extern char const * const unknown_name_7f8724;
extern void *unknown_art_ac1194;
extern void *unknown_art_ac1198;
extern Rect *unknown_rect_ac11c4;
extern Rect *unknown_rect_ac11c8;
extern Rect *unknown_rect_ac11b4;
extern Rect *unknown_rect_ac11cc;
extern Rect *unknown_rect_ac11d0;
extern ShapeFileStruct *unknown_shape_ac10e8;
extern ShapeFileStruct *unknown_shape_ac107c;
extern ShapeFileStruct *unknown_shape_ac10b8;
extern ShapeFileStruct *unknown_shape_ac1044;
extern ShapeFileStruct *unknown_shape_ac10d8;
extern ShapeFileStruct *unknown_shape_ac1060;
extern ConvertClass *unknown_drawer_ac1188;
extern ConvertClass *unknown_drawer_ac1190;
extern ConvertClass *unknown_drawer_ac1198;

void __fastcall Unknown_006F3650(Surface *surface, Rect const &window, bool arg3)
{
    if (!unknown_flag_ac119c) {
        Unknown_0051A2B0();
        Unknown_006F3D50();
        unknown_load_art_6f1fa0(unknown_name_7f871c, &unknown_art_ac1184, (void **)&unknown_art_ac1188);
        unknown_load_art_6f1fa0(unknown_name_7f8720, &unknown_art_ac118c, (void **)&unknown_art_ac1190);
        unknown_load_art_6f1fa0(unknown_name_7f8724, &unknown_art_ac1194, (void **)&unknown_art_ac1198);
        Unknown_006F3E70(unknown_value_8523e0, unknown_value_8523e4);
        unknown_flag_ac119c = true;
    }
    Unknown_006F34D0(surface, window);
    Point2D point(0, 0);
    Rect clip(window.X, window.Y, window.Width, window.Height);
    if (clip.Width > 800) {
        clip.Width = (clip.Width - 800) / 2 + 800;
    }
    if (clip.Height > 600) {
        clip.Height = (clip.Height - 600) / 2 + 600;
    }
    point.X = unknown_rect_ac11c4->X;
    point.Y = unknown_rect_ac11c4->Y;
    CC_Draw_Shape(surface, unknown_drawer_ac1188, unknown_shape_ac10e8, 0, point, clip, 0x400, 0, 0, 0, 1000, 0, 0, Point2D(0, 0));
    int index = 0;
    point.X = unknown_rect_ac11c8->X;
    point.Y = unknown_rect_ac11c8->Y;
    if (unknown_count_ac102c > 0) {
        do {
            CC_Draw_Shape(surface, unknown_drawer_ac1190, unknown_shape_ac107c, 0, point, clip, 0x400, 0, 0, 0, 1000, 0, 0, Point2D(0, 0));
            point.Y += unknown_rect_ac11c8->Height;
            index++;
        } while (index < unknown_count_ac102c);
    }
    if (!arg3) {
        index = 0;
        point.X = unknown_rect_ac11b4->X;
        point.Y = unknown_rect_ac11b4->Y;
        if (unknown_count_ac102c > 0) {
            do {
                CC_Draw_Shape(surface, unknown_drawer_ac1198, unknown_shape_ac10b8, 10, point, clip, 0x400, 0, 0, 0, 1000, 0, 0, Point2D(0, 0));
                point.Y += unknown_rect_ac11b4->Height;
                index++;
            } while (index < unknown_count_ac102c);
        }
    }
    point.X = unknown_rect_ac11cc->X;
    point.Y = unknown_rect_ac11cc->Y;
    CC_Draw_Shape(surface, unknown_drawer_ac1188, unknown_shape_ac1044, 0, point, clip, 0x400, 0, 0, 0, 1000, 0, 0, Point2D(0, 0));
    point.X = unknown_rect_ac11d0->X;
    point.Y = unknown_rect_ac11d0->Y;
    if (unknown_value_8523e0 == 0x280) {
        CC_Draw_Shape(surface, unknown_drawer_ac1188, unknown_shape_ac10d8, 0, point, clip, 0x400, 0, 0, 0, 1000, 0, 0, Point2D(0, 0));
    } else {
        CC_Draw_Shape(surface, unknown_drawer_ac1188, unknown_shape_ac1060, 0, point, clip, 0x400, 0, 0, 0, 1000, 0, 0, Point2D(0, 0));
    }
}
