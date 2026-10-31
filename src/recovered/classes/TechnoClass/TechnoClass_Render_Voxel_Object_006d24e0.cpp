// Original complete object renderer: 814 body bytes plus 2 frozen NOPs.
#include "shared/voxel_cache.hpp"
#include "shared/matrix3d.hpp"
#include "shared/convert.hpp"
#include "shared/surface_blit.hpp"
#include "shared/tactical.hpp"
namespace VoxelDrawSystem {
    void Reset();
    void __fastcall Precalculate_Light(UnknownPairFirst *voxel,int layer,int info,Matrix3D const &motion,Matrix3D const &camera,Vector3 const &light,float scale);
    void __fastcall Prep_For_Object(UnknownPairFirst *voxel,unsigned layer,int info,Matrix3D const &matrix);
    SurfaceRegion __fastcall Render();
}
extern Matrix3D unknown_voxel_transform_839a70;
extern Vector3 unknown_voxel_light_839ab0;
extern BSurface *unknown_surface_ad0604;
extern ConvertClass *unknown_drawer_ad0608;
extern int unknown_int_839638;
// @ref ?unknown_voxel_transform_839a70@@3VMatrix3D@@A=00839a70
// @ref ?unknown_voxel_light_839ab0@@3UVector3@@A=00839ab0
// @ref ?unknown_surface_ad0604@@3PAVBSurface@@A=00ad0604
// @ref ?unknown_drawer_ad0608@@3PAVConvertClass@@A=00ad0608
// @ref ?unknown_int_839638@@3HA=00839638
// @ref ?unknown_tactical_83996c@@3PAVTactical@@A=0083996c
// @ref ?unknown_blit_49f3a0@@YIXAAVSurface@@PAX0ABVRect@@ABURectPoint2D@@2HHHHHH@Z=0049f3a0
SurfaceRegion TechnoClass::Render_Voxel_Object_006d24e0(UnknownObjectPair const &voxel,Matrix3D const &transform,Point2D const &point,Rect const &xcliprect,int frame,unsigned flags,int brightness)
{
    Matrix3D combined;
    combined=transform;
    Matrix3D base;
    base=transform;
    UnknownPairFirst *voxlib=voxel.unknown_00;
    UnknownPairSecond *motion=voxel.unknown_04;
    VoxelDrawSystem::Precalculate_Light(voxlib,0,0,base,unknown_voxel_transform_839a70,unknown_voxel_light_839ab0,3.0f);
    VoxelDrawSystem::Reset();
    for (unsigned layer=0;layer<(unsigned)voxlib->unknown_04;++layer) {
        if (motion) {
            Matrix3D section;
            section=motion->unknown_transforms[((unsigned)frame%motion->unknown_frame_count)*motion->unknown_section_count+layer];
            combined=base*section;
        }
        VoxelDrawSystem::Prep_For_Object(voxlib,layer,0,unknown_voxel_transform_839a70*combined);
    }
    SurfaceRegion region=VoxelDrawSystem::Render();
    if (unknown_slot111() || unknown_slot112()) flags|=4;
    if (House->Unknown_004F52B0() && unknown_slot48()) flags=unknown_slot244(flags);
    Rect cliprect=xcliprect;
    if (unknown_surface_83995c!=unknown_surface_ad0604) {
        if (unknown_322>0) {
            cliprect=Intersect(cliprect,Rect(0,0,unknown_int_839638,unknown_322-unknown_tactical_83996c->unknown_b0.Y));
        } else if (unknown_325) {
            unknown_322=(short)(unknown_tactical_83996c->unknown_b0.Y+point.Y+region.Bounds.Height+region.Point.Y);
        }
    }
    flags&=~0x10U;
    ConvertClass *converter;
    if (Kind_Of()==1 && static_cast<UnitClass *>(this)->unknown_5bb) converter=unknown_drawer_ad0608;
    else converter=(ConvertClass *)unknown_slot115();
    int phase=0;
    if (flags&8) phase=(Fetch_ID()+(int)unknown_1e0)%400;
    Point2D destination=region.Point+point;
    unknown_blit_49f3a0(*unknown_surface_83995c,converter,*VoxelDrawSystem::Get_Surface(),region.Bounds,RectPoint2D(destination.X,destination.Y),cliprect,0,(int)converter->Select_Blitter_00485AA0(flags),unknown_slot176(),unknown_slot177(),brightness,phase);
    return region;
}
// @ref ?Precalculate_Light@VoxelDrawSystem@@YIXPAVUnknownPairFirst@@HHABVMatrix3D@@1ABUVector3@@M@Z=007170d0
// @ref ?Prep_For_Object@VoxelDrawSystem@@YIXPAVUnknownPairFirst@@IHABVMatrix3D@@@Z=007174c0
// @ref ?Render@VoxelDrawSystem@@YI?AUSurfaceRegion@@XZ=007178e0
// @ref ?Reset@VoxelDrawSystem@@YAXXZ=007171d0
// @ref ??D@YI?AVMatrix3D@@ABV0@0@Z=00591180
