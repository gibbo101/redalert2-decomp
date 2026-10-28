// void TechnoClass::unknown_slot267(bool arg1) (0x006D8120, slot 267)
// Keeps the radar point that tracks the object (+0x1A0) current: records
// once whether the map hides the object's position (+0x373), takes the
// radar point of its coordinate (kind 6 keeps the stored point unless
// forced), clips it to the radar surface, and tells slots 264/265 when the
// point appears or moves; while the player's +0x13C timer runs it calls
// slot 266 every Rules FlashFrameTime frames.
#include "shared/techno.hpp"
#include "shared/foot.hpp"
#include "shared/gscreen.hpp"
#include "shared/techno_map.hpp"
#include "shared/rules.hpp"
#include "shared/surface.hpp"
// @ref ?Unknown_00568140@MapClass@@QAE_NABUCoordStruct@@@Z=00568140
// @ref ?Unknown_00631BA0@RadarClass@@QAE?AUPoint2D@@ABUCoordStruct@@_N@Z=00631ba0
// @ref ?Unknown_0055A740@MapClass@@QAE_NPAVCellClass@@_N@Z=0055a740
// @ref ?Unknown_0063B5B0@@YI_NHVCell@@@Z=0063b5b0
// @ref ?unknown_radar_surface_8336f8@@3PAVSurface@@A=008336f8

void TechnoClass::unknown_slot267(bool arg1)
{
    if (!unknown_373 && unknown_game_mode_a3d298 == 0) {
        unknown_373 = !Map.Unknown_00568140(Center_Coord());
    }
    Point2D point;
    if (Kind_Of() == 6 && !arg1) {
        point = unknown_1a0;
    } else {
        point = Map.Unknown_00631BA0(CoordStruct(Coord), false);
    }
    int kind = 0;
    bool visible = unknown_slot190(&kind);
    Rect rect = unknown_radar_surface_8336f8->Get_Rect();
    if (kind != 0 && visible) {
        bool foot;
        if (this != 0) {
            foot = unknown_14_bit2;
        }
        if (this == 0 || !foot || ((FootClass *)this)->unknown_574 < 0) {
            Unknown_0063B5B0(5, Coord_Cell(CoordStruct(Coord)));
        }
    }
    if (!rect.Is_Point_Within(point) && visible) {
        visible = Map.Unknown_0055A740(unknown_slot107(), true);
        if (visible) {
            point = Map.Unknown_00631BA0(CoordStruct(Coord), true);
        }
    }
    if (unknown_37b && (point != unknown_1a0 || !visible)) {
        unknown_slot265();
    }
    unknown_1a0 = point;
    if (!unknown_37b && visible) {
        unknown_slot264();
    }
    if (House == unknown_player_a35db4 && unknown_13c.Value() > 0 && unknown_13c.Value() % Rules->FlashFrameTime == 0) {
        unknown_slot266();
    }
}
