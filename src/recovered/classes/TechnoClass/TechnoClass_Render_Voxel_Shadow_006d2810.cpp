// Original shadow renderer: complete440bytes plus8frozenNOPs.
#include "shared/voxel_cache.hpp"
#include "shared/matrix3d.hpp"
#include "shared/convert.hpp"
#include "shared/surface_blit.hpp"
namespace VoxelDrawSystem {
    void Reset();
    void __fastcall Prep_For_Shadow(UnknownPairFirst *voxel,int layer,int info,Matrix3D const &camera,Matrix3D const &motion,Vector3 const &light,unsigned unknown_1,unsigned unknown_2,unsigned unknown_3);
    SurfaceRegion __fastcall Render();
}
extern Matrix3D unknown_voxel_transform_839a70;
extern Vector3 unknown_839a60;
extern ConvertClass *unknown_drawer_8323c4;
// @ref ?unknown_voxel_transform_839a70@@3VMatrix3D@@A=00839a70
// @ref ?unknown_839a60@@3UVector3@@A=00839a60
// @ref ?unknown_drawer_8323c4@@3PAVConvertClass@@A=008323c4
// @ref ?unknown_blit_49f3a0@@YIXAAVSurface@@PAX0ABVRect@@ABURectPoint2D@@2HHHHHH@Z=0049f3a0
SurfaceRegion TechnoClass::Render_Voxel_Shadow_006d2810(UnknownObjectPair const &voxel,Matrix3D const &transform,Point2D const &point,Rect const &cliprect,int layer,unsigned flags,bool cached,unsigned unknown_1,unsigned unknown_2,unsigned unknown_3)
{
    UnknownPairSecond *motion=voxel.unknown_04;
    Matrix3D combined;
    {
        Matrix3D section_matrix;
        section_matrix=motion->unknown_transforms[(0U%motion->unknown_frame_count)*motion->unknown_section_count+layer];
        combined=transform*section_matrix;
    }
    Matrix3D basis;
    basis.Make_Identity();
    if (unknown_slot32()->ConsideredAircraft) basis.Scale(0.5f);
    VoxelDrawSystem::Reset();
    VoxelDrawSystem::Prep_For_Shadow(voxel.unknown_00,layer,0,unknown_voxel_transform_839a70*basis,combined,unknown_839a60,unknown_1,unknown_2,unknown_3);
    SurfaceRegion region=VoxelDrawSystem::Render();
    if (!cached) {
        (void)VoxelDrawSystem::Get_Surface()->Get_Rect();
        Point2D destination=region.Point+point;
        unknown_blit_49f3a0(*unknown_surface_83995c,unknown_drawer_8323c4,*VoxelDrawSystem::Get_Surface(),region.Bounds,RectPoint2D(destination.X,destination.Y),cliprect,0,(int)unknown_drawer_8323c4->Select_Blitter_00485AA0(flags),unknown_slot176(),unknown_slot177(),1000,0);
    }
    return region;
}
// @ref ?Prep_For_Shadow@VoxelDrawSystem@@YIXPAVUnknownPairFirst@@HHABVMatrix3D@@1ABUVector3@@III@Z=00717360
// @ref ?Render@VoxelDrawSystem@@YI?AUSurfaceRegion@@XZ=007178e0
// @ref ?Reset@VoxelDrawSystem@@YAXXZ=007171d0
// @ref ??D@YI?AVMatrix3D@@ABV0@0@Z=00591180
