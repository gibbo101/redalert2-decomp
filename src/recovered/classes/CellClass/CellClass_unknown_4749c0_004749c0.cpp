// void CellClass::unknown_4749c0(Point2D const &xpoint, Rect const &clip) (0x004749C0):
// Westwood's Draw_Overlay: draws the cell's overlay (bridge decks once per
// frame and view, tiberium through its growth image, walls in the player's
// colours, veins, rubble buildings and ordinary clutter).
#include "shared/cell.hpp"
#include "shared/unknown_static_rect.hpp"
#define SHAPE_FILE_EMPTY_RECT unknown_static_rect
#include "shared/shape_file.hpp"
#include "shared/overlay.hpp"
#include "shared/overlay_type.hpp"
#include "shared/tiberium.hpp"
#include "shared/building_type_class.hpp"
#include "shared/light_convert.hpp"
#include "shared/palette.hpp"
#include "shared/house.hpp"
#include "shared/color_scheme.hpp"
#include "shared/cd_timer.hpp"
#include "shared/unknown_globals.hpp"
// @ref ?Init_Drawer@CellClass@@QAEXPAVLightConvertClass@@HHHHH@Z=004790f0
// @ref ?unknown_surface_83995c@@3PAVSurface@@A=0083995c
// @ref ?CC_Draw_Shape@@YIXPAVSurface@@PAVConvertClass@@PBUShapeFileStruct@@HABUPoint2D@@ABVRect@@HHHHHHHU4@@Z=0049eea0
// @ref ?unknown_drawer_8323b8@@3PAVConvertClass@@A=008323b8
// @ref ?unknown_player_a35db4@@3PAVHouseClass@@A=00a35db4
// @ref ?Frame@@3HA=00a40d2c
// @ref ?unknown_rect_839630@@3VRect@@A=00839630
// @ref ?unknown_redraws_833634@@3EA=00833634
// @ref ?unknown_bridge_variation_7d2b18@@3PAHA=007d2b18
// @ref ?unknown_slope_shapes_a52eb0@@3PAPAXA=00a52eb0

extern unsigned char unknown_redraws_833634;
extern int unknown_bridge_variation_7d2b18[16];
extern void *unknown_slope_shapes_a52eb0[];
extern Rect unknown_rect_839630;

void CellClass::unknown_4749c0(Point2D const &xpoint, Rect const &clip)
{
    if (OverlayIndex == 0xA7 || OverlayIndex == 0xB2) {
        return;
    }
    OverlayTypeClass *otype = OverlayTypes[OverlayIndex];
    Point2D point = unknown_475440() + xpoint;
    int yoffset = 15 * (unknown_11b + (IsBridgeDeck ? 4 : 0));
    point -= clip.Top_Left();
    if (unknown_34 == 0) {
        Init_Drawer(0, 0x10000, 0, 1000, 1000, 1000);
    }
    ShapeFileStruct *shape = (ShapeFileStruct *)otype->unknown_slot39();
    if (IsBridgeDeck) {
        if (unknown_64 != Frame || unknown_118 != unknown_redraws_833634
            || unknown_68 != clip) {
            int shapenum = OverlayData;
            if (shapenum == 0 || shapenum == 9) {
                shapenum += unknown_bridge_variation_7d2b18[(MapCoords.X & 3) | (4 * (MapCoords.Y & 3))];
            }
            CC_Draw_Shape(unknown_surface_83995c, unknown_34, shape, shapenum, point, clip, 0x4E00, 0, -2 - yoffset, 0, unknown_10e, 0, 0, Point2D(0, 0));
            unknown_64 = Frame;
            unknown_68 = unknown_rect_839630;
            unknown_118 = unknown_redraws_833634;
        }
        return;
    }
    if (otype->Tiberium) {
        int tib = Get_Tiberium_Type();
        if (tib == -1) {
            return;
        }
        TiberiumClass *tiberium = unknown_TiberiumClass_list_00ac0b30[tib];
        OverlayTypeClass *tib_overlay;
        if (unknown_11c != 0) {
            tib_overlay = OverlayTypes[tiberium->Image->ArrayIndex + tiberium->NumFrames + tiberium->NumImages / 4 * (unknown_11c - 1) + MapCoords.X * MapCoords.Y % (tiberium->NumImages / 4)];
        } else {
            tib_overlay = OverlayTypes[tiberium->Image->ArrayIndex + MapCoords.X * MapCoords.Y % tiberium->NumFrames];
        }
        ShapeFileStruct *tibshape = (ShapeFileStruct *)tib_overlay->unknown_slot39();
        if (unknown_11c != 0) {
            CC_Draw_Shape(unknown_surface_83995c, unknown_drawer_8323b8, tibshape, OverlayData, point, clip, 0x4E00, 0, -2 - yoffset, 0, 1000, (int)unknown_slope_shapes_a52eb0[unknown_11c - 1], 0, Point2D(0, 0));
        } else {
            CC_Draw_Shape(unknown_surface_83995c, unknown_drawer_8323b8, tibshape, OverlayData, point, clip, 0x4E00, 0, -2 - yoffset, 0, 1000, 0, 0, Point2D(0, 0));
        }
    } else if (otype->Wall) {
        CC_Draw_Shape(unknown_surface_83995c, ColorSchemes[unknown_player_a35db4->ColorSchemeIndex]->Converter, shape, OverlayData, point, clip, 0x4E00, 0, -2 - yoffset, 2, unknown_10a, 0, 0, Point2D(0, 0));
    } else if (otype->ArrayIndex == 0x7E) {
        if (unknown_11c != 0) {
            CC_Draw_Shape(unknown_surface_83995c, unknown_drawer_8323b8, shape, OverlayData, point, clip, 0x4E00, 0, -2 - yoffset, 0, unknown_10c, (int)unknown_slope_shapes_a52eb0[unknown_11c - 1], 0, Point2D(30, -2));
        } else {
            CC_Draw_Shape(unknown_surface_83995c, unknown_drawer_8323b8, shape, OverlayData, point, clip, 0x4E00, 0, -2 - yoffset, 0, unknown_10c, 0, 0, Point2D(0, 0));
        }
    } else {
        bool flat = otype->DrawFlat;
        int offsety = flat ? 0 : -15;
        if (otype->IsARock) {
            offsety = 0;
        }
        if (otype->Crate) {
            CC_Draw_Shape(unknown_surface_83995c, unknown_34, shape, 0, point, clip, 0x4E00, 0, offsety - yoffset - 2, flat ? 0 : 2, unknown_10c, 0, 0, Point2D(0, 0));
        } else if (otype->IsRubble) {
            if (unknown_40 != 0) {
                ShapeFileStruct *image;
                int frame;
                if (((BuildingTypeClass *)unknown_40)->unknown_func_458e00((void **)&image, &frame)) {
                    CC_Draw_Shape(unknown_surface_83995c, unknown_34, image, frame, point, clip, 0x4E00, 0, offsety - yoffset - 2, flat ? 0 : 2, unknown_10c, 0, 0, Point2D(0, 0));
                }
            }
        } else {
            CC_Draw_Shape(unknown_surface_83995c, unknown_34, shape, OverlayData, point, clip, 0x4E00, 0, offsety - yoffset - 2, flat ? 0 : 2, unknown_10c, 0, 0, Point2D(0, 0));
        }
    }
}
