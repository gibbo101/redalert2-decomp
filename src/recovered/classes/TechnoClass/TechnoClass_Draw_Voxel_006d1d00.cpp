#include "shared/voxel_cache.hpp"
extern Rect unknown_unit_rect_ad0490;
// @ref ?unknown_unit_rect_ad0490@@3VRect@@A=00ad0490
void TechnoClass::unknown_slot246(UnknownObjectPair const &voxel,int frame,int key,UnknownBuffer *cache,Rect const &cliprect,Point2D const &draw_point,Matrix3D const &transform,int brightness,unsigned negflags)
{
    unsigned flags=0x2000;
    if (!negflags) {
        switch (unknown_slot25(false,0)) {
        case 4: {
            // Reference distinguishes ripple stages0,1,and later stages.
            int stage=unknown_1bc.Fetch_Stage();
            if (stage==0) flags=0x200a;
            else if (stage==1) flags=0x200c;
            else flags=0x200c;
            break;
        }
        case 1: flags=0x2002; break;
        case 2: case 3: flags=0x2004; break;
        case 5: return;
        }
    }
    if ((unknown_slot111() || unknown_slot112()) && (Kind_Of()!=1 || !((UnitClass *)this)->unknown_5bb)) flags|=0x2004;
    if (House->Unknown_004F52B0() && unknown_slot48() && (Kind_Of()!=1 || !((UnitClass *)this)->unknown_5bb)) flags=unknown_slot244(flags);
    flags=(flags|0x800)&~negflags;
    Rect window=cliprect;
    brightness=unknown_slot254(brightness);
    if (unknown_slot203()) brightness=unknown_6d86f0(brightness);
    if (key!=-1) {
        if (!cache || unknown_slot32()->DisableVoxelCache) key=-1;
        else {
            void *entry=(*cache)[key];
            if (entry) {
                Blit_Voxel_006d29d0(entry,draw_point,window,flags,brightness);
                return;
            }
        }
    }
    if (!voxel.unknown_00 || !voxel.unknown_04) return;
    SurfaceRegion region=Render_Voxel_Object_006d24e0(voxel,transform,draw_point,window,frame,flags,brightness);
    int height=region.Bounds.Height;
    int width=region.Bounds.Width;
    if (Kind_Of()==1) unknown_unit_rect_ad0490=Union(unknown_unit_rect_ad0490,Rect(region.Point.X+draw_point.X,region.Point.Y+draw_point.Y,width,height));
    if (key==-1) return;
    void *data=unknown_voxel_static_buffer_839aa0.Add(*VoxelDrawSystem::Get_Surface(),region);
    if (!data || !cache->Add_Index(key,data)) {
        Class_Of()->Clear_Voxel_Indexes();
        if (!data) data=unknown_voxel_static_buffer_839aa0.Add(*VoxelDrawSystem::Get_Surface(),region);
        cache->Add_Index(key,data);
    }
}
// @ref ?Add@StaticBufferClass@@QAEPAUEntry@1@AAVSurface@@ABUSurfaceRegion@@@Z=0069a1d0
// @ref ?Blit_Voxel_006d29d0@TechnoClass@@QAEXPBXABUPoint2D@@ABVRect@@IH@Z=006d29d0
// @ref ?Render_Voxel_Object_006d24e0@TechnoClass@@QAE?AUSurfaceRegion@@ABVUnknownObjectPair@@ABVMatrix3D@@ABUPoint2D@@ABVRect@@HIH@Z=006d24e0
