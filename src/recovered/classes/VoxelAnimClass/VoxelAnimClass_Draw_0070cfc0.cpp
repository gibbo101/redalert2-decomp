// void VoxelAnimClass::unknown_slot67(int screen_point_arg, int clip_rect_arg) (0x0070CFC0, slot 67)
// Draws the voxel animation at the screen point screen_point_arg within the window clip_rect_arg:
// its shadow (the voxel flattened onto the ground) and then the voxel itself,
// lit and rotated by the bounce state.
#include "shared/voxel_anim.hpp"
#include "shared/id_source.hpp"
#include "shared/cell.hpp"
#include "shared/map_view.hpp"
#include "shared/tactical.hpp"
#include "shared/matrix3d.hpp"
#include "shared/house.hpp"
#include "shared/color_scheme.hpp"
#include "shared/surface_blit.hpp"
#include "shared/convert.hpp"
void __fastcall Prepare_Voxel_Lighting_00717050(UnknownPairFirst *voxel, int section, int arg3, Matrix3D const &matrix, Vector3 const &light);
void __cdecl Reset_Voxel_Renderer_007171d0();
void __fastcall Add_Voxel_Section_007174c0(UnknownPairFirst *voxel, unsigned section, int arg3, Matrix3D const &matrix);
void __fastcall Voxel_Draw_Section_00717360(UnknownPairFirst *voxel, int section, int arg3, Matrix3D const &transform, Matrix3D const &matrix, Vector3 const &light, int a7, int a8, int a9);
void __fastcall Voxel_Render_Bounds_007176c0(Rect *rect, int *x, int *y);
Surface &__cdecl Voxel_Render_Surface_00717040();
extern Matrix3D unknown_voxel_transform_839a70;
extern Vector3 unknown_voxel_shadow_light_839a60;
extern Vector3 unknown_voxel_light_839ab0;
extern ConvertClass *unknown_drawer_8323b4;
extern ConvertClass *unknown_drawer_8323bc;
// @ref ?Voxel_Draw_Section_00717360@@=00717360
// @ref ?Voxel_Render_Bounds_007176c0@@=007176c0
// @ref ??D@YI?AVMatrix3D@@ABV0@0@Z=00591180
// @ref ?Prepare_Voxel_Lighting_00717050@@=00717050
// @ref ?Reset_Voxel_Renderer_007171d0@@=007171d0
// @ref ?Add_Voxel_Section_007174c0@@=007174c0
// @ref ?Voxel_Render_Surface_00717040@@=00717040
// @ref ?unknown_voxel_transform_839a70@@=00839a70
// @ref ?unknown_voxel_shadow_light_839a60@@=00839a60
// @ref ?unknown_voxel_light_839ab0@@=00839ab0
// @ref ?unknown_drawer_8323b4@@=008323b4
// @ref ?unknown_drawer_8323bc@@=008323bc
// @ref ?Select_Blitter_00485AA0@ConvertClass@@=00485aa0
// @ref ?Unknown_006A2970@@YIHH@Z=006a2970
// @ref ?Unknown_005683C0@MapClass@@=005683c0
// @ref ?Unknown_0055A280@MapClass@@=0055a280
// @ref ?unknown_surface_83995c@@3PAVSurface@@A=0083995c
// @ref ?unknown_tactical_83996c@@3PAVTactical@@A=0083996c
// @ref ?unknown_matrix_436fc0@BounceClass@@QBE?AVMatrix3D@@XZ=00436fc0
void VoxelAnimClass::unknown_slot67(int screen_point_arg, int clip_rect_arg)
{
    Point2D const *point = (Point2D const *)screen_point_arg;
    Rect const *window = (Rect const *)clip_rect_arg;
    if ((unknown_id_source_a3d290->unknown_000 & 0x1000) != 0) {
        CoordStruct coord = Coord;
        if (Map.Unknown_005683C0(coord)) return;
    }
    Point2D pixel;
    Point2D position = *point;
    int level;
    CoordStruct ground = Coord;
    ground.Z = Map.Unknown_0055A280(ground);
    CellClass &cell = Map[ground];
    {
                if ((cell.unknown_140 & 0x100) != 0 && (CoordStruct(Coord).Z >= unknown_geometry_j + ground.Z)) {
            level = unknown_geometry_j + ground.Z;
            CoordStruct raised = ground + CoordStruct(0, 0, unknown_geometry_j + 1);
            unknown_tactical_83996c->Coord_To_Pixel(raised, pixel);
        } else {
            level = ground.Z;
            unknown_tactical_83996c->Coord_To_Pixel(ground, pixel);
        }
    }
    if (unknown_124) return;
    UnknownPairFirst *voxel = Class->unknown_b0.unknown_00;
    if (voxel == 0) return;
    Matrix3D matrix;
    matrix = BounceClass::unknown_matrix_436fc0();
    Reset_Voxel_Renderer_007171d0();
    Voxel_Draw_Section_00717360(voxel, Class->VoxelIndex, 0, unknown_voxel_transform_839a70, matrix, unknown_voxel_shadow_light_839a60, 0, 0, 0);
    Rect rect;
    int offset_y;
    int offset_x;
    Voxel_Render_Bounds_007176c0(&rect, &offset_x, &offset_y);
    {
        RectPoint2D draw(pixel.X + offset_x, pixel.Y + offset_y);
        unknown_blit_49f3a0(*unknown_surface_83995c, unknown_drawer_8323b4, Voxel_Render_Surface_00717040(), rect, draw, *window, 0,
                            (int)unknown_drawer_8323b4->Select_Blitter_00485AA0(0x2001), -4 - Unknown_006A2970(level), 0, 1000, 0);
    }
    matrix = BounceClass::unknown_matrix_436fc0();
    Prepare_Voxel_Lighting_00717050(voxel, 0, 0, matrix, unknown_voxel_light_839ab0);
    Reset_Voxel_Renderer_007171d0();
    Add_Voxel_Section_007174c0(voxel, Class->VoxelIndex, 0, unknown_voxel_transform_839a70 * matrix);
    Voxel_Render_Bounds_007176c0(&rect, &offset_x, &offset_y);
    int flags = 0x2800;
    if (Class->Translucent) {
        flags = 0x2804;
    }
    int brightness;
    {
        CoordStruct coord = Coord;
        brightness = Map[coord].unknown_10a;
    }
    ConvertClass *drawer;
    if (unknown_f4 != 0) {
        drawer = ColorSchemes[unknown_f4->ColorSchemeIndex]->Converter;
    } else if (Class->IsTiberium) {
        drawer = unknown_drawer_8323bc;
    } else {
        drawer = unknown_drawer_8323b4;
        brightness = 1000;
    }
    {
        RectPoint2D draw2(position.X + offset_x, position.Y + offset_y);
        unknown_blit_49f3a0(*unknown_surface_83995c, drawer, Voxel_Render_Surface_00717040(), rect, draw2, *window, 0,
                            (int)drawer->Select_Blitter_00485AA0(flags), -2 - Unknown_006A2970(unknown_slot110()), 0, brightness, 0);
    }
}
