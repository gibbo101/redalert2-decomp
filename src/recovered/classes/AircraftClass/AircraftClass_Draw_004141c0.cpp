// Aircraft drawing: original 0x004141C0, 1256 bytes plus 8 alignment NOPs.
// COM plain-value returns and explicit coordinate conversion follow the original ABI.
#include "shared/aircraft.hpp"
#include "shared/map_view.hpp"
#include "shared/tactical.hpp"
#include "shared/matrix3d.hpp"
#include "shared/house.hpp"
#include "shared/team.hpp"
#include "shared/id_source.hpp"
#include "shared/anim.hpp"
#include "shared/rules.hpp"

Matrix3D __fastcall Aircraft_Isometric_View_Matrix_00717f90();
// @ref ?Aircraft_Isometric_View_Matrix_00717f90@@YI?AVMatrix3D@@XZ=00717f90

void AircraftClass::unknown_slot67(int screen_point_address, int clip_address)
{
    if (!unknown_flag_a40d13 && unknown_b263d8 &&
        (unknown_id_source_a3d290->unknown_000 & 0x1000)) {
        CoordStruct destination = (CoordStruct)Locomotor.Checked()->Head_To_Coord();
        destination.Z = Position_Coord_004f3f40().Z;
        if (Map.Unknown_005683C0(destination) &&
            Map.Unknown_005683C0(Position_Coord_004f3f40()) && !House->Unknown_004F52B0()) return;
    }

    Point2D draw_point = *reinterpret_cast<Point2D const *>(screen_point_address);
    draw_point += Locomotor.Checked()->Draw_Point();
    if (Cargo.Object && Type->Carryall) {
        Cargo.unknown_468a10()->unknown_slot67(reinterpret_cast<int>(&draw_point), clip_address);
    }
    unknown_slot104();
    if (Type->unknown_206 && Type->unknown_b0.unknown_00) {
        CoordStruct ground = Position_Coord_004f3f40();
        ground.Z = Map.Unknown_0055A280(ground);
        Point2D shadow_point;
        unknown_tactical_83996c->Coord_To_Pixel(ground, shadow_point);
        shadow_point += Locomotor.Checked()->Shadow_Point();

        int key = 0;
        int saved_height = unknown_slot108();
        bool saved_flag = unknown_slot47();
        unknown_5a0 = false;
        UnknownCellClass *cell = reinterpret_cast<UnknownCellClass *>(&Map[Position_Coord_004f3f40()]);
        bool draw_on_ground = false;
        if ((unknown_79 || saved_height < unknown_geometry_j) &&
            (!unknown_79 || saved_height < 0)) {
            draw_on_ground = true;
        } else {
            if ((cell->Flags & 0x100) &&
                (((cell->Flags & 0x800) && (cell->Unknown_00476AC0(0)->Flags & 0x100)) ||
                 (!(cell->Flags & 0x800) && (cell->Unknown_00476AC0(6)->Flags & 0x100)))) {
                unknown_slot109(unknown_geometry_j);
                shadow_point.Y -= Unknown_006A2970(unknown_geometry_j);
            } else {
                draw_on_ground = true;
            }
        }
        if (draw_on_ground) unknown_slot109(0);

        Matrix3D matrix;
        matrix = Locomotor.Checked()->Shadow_Matrix(&key);
        if (!unknown_325) {
            unknown_4c9a40(Type->unknown_b0, 0,
                key, &Type->unknown_23c,
                *reinterpret_cast<Rect const *>(clip_address), shadow_point,
                Aircraft_Isometric_View_Matrix_00717f90() * matrix, true, 0, 0, 0);
        }
        unknown_slot109(saved_height);
        unknown_5a0 = saved_flag;
        unknown_tactical_83996c->Unknown_006AA510(this, draw_point.X, draw_point.Y);

        int scenario_scale;
        if (Unknown_0051FC50()) scenario_scale = unknown_id_source_a3d290->IonLevel;
        else scenario_scale = unknown_id_source_a3d290->AmbientLevel;
        int level = unknown_slot108() / (unknown_geometry_g + unknown_geometry_g);
        int altitude_term = level * scenario_scale;
        UnknownCellClass *ground_cell = reinterpret_cast<UnknownCellClass *>(&Map[ground]);
        int shadow_height = ground_cell->unknown_10a + Rules->ExtraAircraftLight;
        shadow_height += altitude_term;
        key = 0;
        matrix = Locomotor.Checked()->Draw_Matrix(&key);
        unknown_slot246(Type->unknown_b0, 0,
            key, &Type->unknown_214,
            *reinterpret_cast<Rect const *>(clip_address), draw_point,
            Aircraft_Isometric_View_Matrix_00717f90() * matrix, shadow_height, 0);
    }
    // Original base draw receives the ORIGINAL first argument, not draw_point.
    FootClass::unknown_slot67(screen_point_address, clip_address);
}

// @ref ??0Matrix3D@@QAE@ABUCOMMatrix3DStruct@@@Z=0058fe10

// @ref ??D@YI?AVMatrix3D@@ABV0@0@Z=00591180
