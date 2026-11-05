// void UnitClass::unknown_slot67(int point_arg, int window_arg) (0x00700E70, slot 67)
// TibSun UnitClass::Draw_It.
#include "shared/unit.hpp"
#include "shared/cell.hpp"
#include "shared/map_view.hpp"
#include "shared/rules.hpp"
#include "shared/house.hpp"
#include "shared/tactical.hpp"
#include "shared/palette.hpp"
#include "shared/id_source.hpp"
#include "shared/mix_file_class.hpp"
#include "shared/color_scheme.hpp"
#include "shared/fast_math.hpp"
#include "shared/building_light.hpp"
#include "shared/unknown_globals.hpp"
extern int unknown_bridge_height_ad057c;
bool Unknown_0051FC50();
bool Unknown_0051FC60();
// @ref ?unknown_bridge_height_ad057c@@3HA=00ad057c
// @ref ?unknown_facing_radians_79b620@@3NB=0079b620
// @ref ?Unknown_0051FC50@@YA_NXZ=0051fc50
// @ref ?Unknown_0051FC60@@YA_NXZ=0051fc60
// @ref ??_C@_0M@KLGB@FLAGFLY?4SHP?$AA@=007f8f74
// @ref ??_C@_0M@CCJA@OREGATH?4SHP?$AA@=007f8f80
// @ref _?$S49@?1??unknown_slot67@UnitClass@@UAEXHH@Z@4EA=00ad0578
// @ref _?harvesting_shape@?1??unknown_slot67@UnitClass@@UAEXHH@Z@4PBUShapeFileStruct@@B=00ad0468
// @ref __real@8@4003f000000000000000=007ae2e0
// @ref ?_com_issue_error@@YGXJ@Z=00795940
// @ref ?unknown_slot67@FootClass@@=004c9bc0
// By value: the Move_Coord result is built after radians dies and shares its slot.
inline bool Coord_Pixel_00700e70(CoordStruct coord, Point2D &pixel)
{
    return unknown_tactical_83996c->Coord_To_Pixel(coord, pixel);
}

inline double Radian_00700e70(UnknownFacingDir const &dir)
{
    return ((short)dir.Raw - 0x3FFF) * unknown_facing_radians_79b620;
}
inline CoordStruct Move_Coord_00700e70(CoordStruct const &start, UnknownFacingDir const &dir, int distance)
{
    double radians = Radian_00700e70(dir);
    return CoordStruct((int)(start.X + unknown_cos_4ba4d0(radians) * distance), (int)(start.Y - unknown_sin_4ba480(radians) * distance), start.Z);
}

void UnitClass::unknown_slot67(int point_arg, int window_arg)
{
    static ShapeFileStruct const *harvesting_shape = (ShapeFileStruct const *)MixFileClass::Retrieve("OREGATH.SHP");
    Point2D const &input = *reinterpret_cast<Point2D const *>(point_arg);
    Rect const &window = *reinterpret_cast<Rect const *>(window_arg);

    Point2D adjusted_point = input;
    adjusted_point.Y -= *reinterpret_cast<signed char const *>(&unknown_59e);
    Point2D raw_point = adjusted_point;
    if (unknown_37c) {
        adjusted_point.Y += 14;
    }
    Cell cell = unknown_slot104();
    if (unknown_slot25(false, 0) != 5) {
        unknown_tactical_83996c->Unknown_006AA510(this, adjusted_point.X, adjusted_point.Y);
        int height = unknown_slot108();
        CellClass *cptr = &Map[CoordStruct(Coord)];
        int brightness;
        if (((!unknown_79 && height >= unknown_bridge_height_ad057c) || (unknown_79 && height >= 0))
            && (cptr->unknown_140 & 0x100)
            && (((cptr->unknown_140 & 0x800) && (cptr->Adjacent_Cell(0).unknown_140 & 0x100))
                || (!(cptr->unknown_140 & 0x800) && (cptr->Adjacent_Cell(6).unknown_140 & 0x100)))) {
            int level;
            if (Unknown_0051FC50()) {
                level = unknown_id_source_a3d290->IonLevel;
            } else if (Unknown_0051FC60()) {
                level = unknown_id_source_a3d290->unknown_22f4;
            } else {
                level = unknown_id_source_a3d290->AmbientLevel;
            }
            brightness = Map[cell].unknown_10a + 4 * level;
        } else {
            int shade = 0;
            if ((Map[cell].unknown_140 & 0x10000) && !unknown_slot21()) {
                shade = -500;
            }
            brightness = Map[cell].unknown_10a + shade;
        }
        brightness += Rules->ExtraUnitLight;

        if (Type->Harvester && unknown_5ba && !Locomotor.Checked()->Is_Moving_Now()) {
            Point2D pixel;
            int face = Dir_To_8(unknown_2e0.Current());
            Coord_Pixel_00700e70(Move_Coord_00700e70(unknown_slot42(), Facing_Dir(face), 30), pixel);
            int offset = Dir_To_8(unknown_2e0.Current());
            offset = 7 - offset;
            if (unknown_20c == 0 && !unknown_slot111() && !unknown_slot112()) {
                CC_Draw_Shape(unknown_surface_83995c, Unit_Draw_Convert_008323C0, harvesting_shape,
                    (unknown_430 + Frame) % 15 + offset * 15, pixel, window, 0x2a00, 0,
                    unknown_slot176() - 2, 0, brightness, 0, 0, Point2D(0, 0));
            }
        }

        UnitTypeClass *oldclass = Type;
        if (Type->Harvester && unknown_5b9 && oldclass->UnloadingClass != 0) {
            Type = oldclass->UnloadingClass;
        }
        ObjectTypeClass *type = Type;
        if (!unknown_slot245(unknown_player_a35db4)) {
            type = unknown_slot50(true);
        }
        if (unknown_574 == -1) {
            if (type->unknown_206) {
                if (type->unknown_b0.unknown_00 != 0) {
                    unknown_slot310(adjusted_point, window, brightness);
                }
            } else {
                unknown_slot311(adjusted_point, window, brightness);
            }
        }
        Type = oldclass;
        if (unknown_5b4 != -1) {
            CC_Draw_Shape(unknown_surface_83995c, ColorSchemes[Houses[unknown_5b4]->ColorSchemeIndex]->Converter,
                (ShapeFileStruct const *)MixFileClass::Retrieve("FLAGFLY.SHP"), Frame % 14, raw_point, window, 0xa00,
                0, 0, 0, brightness, 0, 0, Point2D(0, 0));
        }
        FootClass::unknown_slot67(reinterpret_cast<int>(&raw_point), window_arg);
        if (unknown_314.Value() != 0) {
            unknown_6cc020();
        }
    }
}
