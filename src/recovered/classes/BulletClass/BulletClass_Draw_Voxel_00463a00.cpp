// Bullet voxel drawing00463A00: complete original408+8, ABI/layout hypotheses.
#include "shared/bullet.hpp"
#include "shared/bullet_type.hpp"
#include "shared/matrix3d.hpp"
#include "shared/text_print.hpp"
#include "shared/surface_blit.hpp"
struct BulletVoxelBounds {
    RectPoint2D offset; // first8, original463B0C/463B10
    Rect rectangle; // +08, original463B6C LEA passes this field
};
void __fastcall Prepare_Voxel_Lighting_00717050(UnknownPairFirst *voxel, int section, int arg3, Matrix3D const &matrix, Vector3 const &light);
void __cdecl Reset_Voxel_Renderer_007171d0();
void __fastcall Add_Voxel_Section_007174c0(UnknownPairFirst *voxel, unsigned section, int arg3, Matrix3D const &matrix);
BulletVoxelBounds __fastcall Voxel_Render_Bounds_007178e0();
Surface &__cdecl Voxel_Render_Surface_00717040();
extern Matrix3D unknown_voxel_transform_839a70;
extern Vector3 unknown_voxel_light_839ab0;
extern int unknown_flat_voxel_7d11a4;
// @ref ?Draw_Voxel_00463a00@BulletClass@@=00463a00
// @ref ??D@YI?AVMatrix3D@@ABV0@0@Z=00591180
// @ref ?Prepare_Voxel_Lighting_00717050@@=00717050
// @ref ?Reset_Voxel_Renderer_007171d0@@=007171d0
// @ref ?Add_Voxel_Section_007174c0@@=007174c0
// @ref ?Voxel_Render_Bounds_007178e0@@=007178e0
// @ref ?Voxel_Render_Surface_00717040@@=00717040
// @ref ?unknown_voxel_transform_839a70@@=00839a70
// @ref ?unknown_voxel_light_839ab0@@=00839ab0
// @ref ?unknown_flat_voxel_7d11a4@@=007d11a4
// @ref ?Select_Blitter_00485AA0@ConvertClass@@=00485aa0
// @ref ?unknown_blit_49f3a0@@YIXAAVSurface@@PAX0ABVRect@@ABURectPoint2D@@2HHHHHH@Z=0049f3a0
void BulletClass::Draw_Voxel_00463a00(UnknownObjectPair const &pair, Matrix3D const &matrix,
                                   RectPoint2D const &point, Rect const &window, unsigned frame,
                                   unsigned flags, int brightness)
{
    UnknownPairFirst *voxel = pair.unknown_00;
    UnknownPairSecond *motion = pair.unknown_04;
    Prepare_Voxel_Lighting_00717050(voxel, 0, 0, matrix, unknown_voxel_light_839ab0);
    Reset_Voxel_Renderer_007171d0();
    // Original leaves this uninitialized if sections exist but motion is null;
    // valid caller inputs/precondition remain to be evidenced.
    Matrix3D transformed;
    for (unsigned section = 0; section < (unsigned)voxel->unknown_04; ++section) {
        if (motion != 0) {
            Matrix3D section_matrix;
            section_matrix = motion->unknown_transforms[(frame % motion->unknown_frame_count) * motion->unknown_section_count + section];
            transformed = matrix * section_matrix;
        }
        Add_Voxel_Section_007174c0(voxel, section, 0, unknown_voxel_transform_839a70 * transformed);
    }
    BulletVoxelBounds bounds = Voxel_Render_Bounds_007178e0();
    int flat = 0;
    unsigned draw_flags = flags & ~0x10;
    if (Type->Flat) {
        flat = unknown_flat_voxel_7d11a4;
        draw_flags |= 0x2000;
    }
    unknown_blit_49f3a0(*unknown_surface_83995c, ColorSchemes[Type->Color]->Converter, Voxel_Render_Surface_00717040(),
                       bounds.rectangle, point + bounds.offset, window, 0,
                       (int)ColorSchemes[Type->Color]->Converter->Select_Blitter_00485AA0(draw_flags), flat,
                       Type->Flat ? 0 : 2, brightness, 0);
}

// Genuine shared point-sum operation; complete emitted copy binds435540.
RectPoint2D RectPoint2D::operator+(RectPoint2D const &point) const { return RectPoint2D(X + point.X, Y + point.Y); }
