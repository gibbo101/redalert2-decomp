// void OverlayClass::unknown_slot68(int arg1, int arg2) (0x005DBD00)
// Draws the overlay's image (a pixel point and a clip rectangle are passed
// as addresses): ore uses its type's colour scheme at a fixed brightness,
// veins the owner's, and everything else the cell's drawer and light level.
#define SHAPE_FILE_EMPTY_RECT unknown_static_rect
#include "shared/overlay.hpp"
#include "shared/map_view.hpp"
#include "shared/tactical.hpp"
#include "shared/palette.hpp"
#include "shared/text_print.hpp"
#include "shared/tiberium.hpp"
#include "shared/anim_type.hpp"
#include "shared/house.hpp"
// @ref ?Unknown_006A2970@@YIHH@Z=006a2970
// @ref ?CC_Draw_Shape@@YIXPAVSurface@@PAVConvertClass@@PBUShapeFileStruct@@HABUPoint2D@@ABVRect@@HHHHHHHU4@@Z=0049eea0
// @ref ?Unknown_0055A280@MapClass@@QAEHABUCoordStruct@@@Z=0055a280
// @ref ?unknown_int_839634@@3HA=00839634
// @ref ?unknown_short_8325d0@@3FA=008325d0

// The index of an overlay type in OverlayTypes (the list's ID lookup, expanded here).
inline int Overlay_Type_Index(OverlayTypeClass *type)
{
    for (int index = 0; index < OverlayTypes.Count(); index++) {
        if (OverlayTypes[index] == type) {
            return index;
        }
    }
    return -1;
}

int __fastcall Unknown_006A2970(int distance);              // 0x006A2970
extern int unknown_int_839634;                              // 0x00839634
extern short unknown_short_8325d0;                          // 0x008325D0

void OverlayClass::unknown_slot68(int arg1, int arg2)
{
    Point2D const *point = (Point2D const *)arg1;
    Rect const *window = (Rect const *)arg2;
    void *shape = Class->unknown_slot39();
    int height = Unknown_006A2970(Map.Unknown_0055A280(CoordStruct(Coord)));
    int overlay = Overlay_Type_Index(Class);
    Point2D position = Point2D(point->X, point->Y + Draw_Offset(overlay).Y);
    position.Y += unknown_int_839634;
    if (Class->Tiberium) {
        TiberiumClass *tiberium = unknown_TiberiumClass_list_00ac0b30[To_Tiberium(Overlay_Type_Index(Class))];
        ColorScheme *scheme = ColorSchemes[tiberium->unknown_c0];
        shape = OverlayTypes[tiberium->Image->ArrayIndex]->unknown_slot39();
        if (!shape && Class->CellAnim) {
            shape = Class->CellAnim->unknown_slot39();
        }
        CC_Draw_Shape(unknown_surface_83995c, scheme->Converter, (ShapeFileStruct const *)shape, 0, position, *window,
                      0xE00, 0, -2 - height, 0, 1000, 0, 0, Point2D(0, 0));
    } else if (Class->IsVeins) {
        if (Class->ArrayIndex == 0xA7) {
            position.Y -= 0x26;
        }
        Point2D origin(0, 0);
        CC_Draw_Shape(unknown_surface_83995c, ColorSchemes[unknown_player_a35db4->ColorSchemeIndex]->Converter, (ShapeFileStruct const *)shape, 0, position, *window,
                      0xE00, 0, -2 - height, 0, Map[CoordStruct(Coord)].unknown_10c, 0, 0, origin);
    } else {
        CellClass *drawn;
        if (Map.Unknown_0054AAB0(Coord_Cell(CoordStruct(Coord)))) {
            drawn = &Map[CoordStruct(Coord)];
        } else if (Map.Unknown_0054AAB0(unknown_tactical_83996c->Unknown_006A6BD0(position))) {
            drawn = &Map[unknown_tactical_83996c->Unknown_006A6BD0(position)];
        } else {
            drawn = &Map[Cell(1, unknown_short_8325d0)];
        }
        CC_Draw_Shape(unknown_surface_83995c, (ConvertClass *)drawn->unknown_34, (ShapeFileStruct const *)shape, 0, position, *window,
                      0xE00, 0, -2 - height, 0, drawn->unknown_10c, 0, 0, Point2D(0, 0));
    }
}
