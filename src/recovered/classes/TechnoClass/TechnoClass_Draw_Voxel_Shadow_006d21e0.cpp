#include "shared/voxel_cache.hpp"
// @ref ?unknown_voxel_static_buffer_839aa0@@3VStaticBufferClass@@A=00839aa0
// @ref ?unknown_cache_empty_b2b624@@3PAXA=00b2b624
// @ref ?Get_Surface@VoxelDrawSystem@@YAPAVSurface@@XZ=00717040
// Complete original shadow draw764body+4padding, eleven stack arguments.
void TechnoClass::Unknown_006D21E0(UnknownObjectPair const &voxel,int layer,int key,UnknownBuffer *cache,Rect const &cliprect,Point2D const &draw_point,Matrix3D const &transform,bool force_cache,unsigned unknown_1,unsigned unknown_2,unsigned unknown_3)
{
    if (unknown_1b8 || unknown_slot32()->NoShadow || voxel.unknown_00->unknown_00) return;
    if (key!=-1) {
        if (!cache || unknown_slot32()->DisableShadowCache) key=-1;
        else {
            void *entry=(*cache)[key];
            if (entry) {
                Blit_Voxel_006d29d0(entry,draw_point,cliprect,0x2001,1000);
                return;
            }
            if (!force_cache) return;
        }
    }
    SurfaceRegion region=Render_Voxel_Shadow_006d2810(voxel,transform,draw_point,cliprect,layer,0x2001,key!=-1,unknown_1,unknown_2,unknown_3);
    if (key!=-1) {
        bool added=true;
        void *data=unknown_voxel_static_buffer_839aa0.Add(*VoxelDrawSystem::Get_Surface(),region);
        if (!data || !cache->Add_Index(key,data)) {
            added=false;
            Class_Of()->Clear_Voxel_Indexes();
            if (!data) data=unknown_voxel_static_buffer_839aa0.Add(*VoxelDrawSystem::Get_Surface(),region);
        }
        if (!added) cache->Add_Index(key,data);
        Unknown_006D21E0(voxel,layer,key,cache,cliprect,draw_point,transform,false,0,0,0);
    }
}
// @ref ?Unknown_006D21E0@TechnoClass@@QAEXABVUnknownObjectPair@@HHPAVUnknownBuffer@@ABVRect@@ABUPoint2D@@ABVMatrix3D@@_NIII@Z=006d21e0
// @ref ?Render_Voxel_Shadow_006d2810@TechnoClass@@QAE?AUSurfaceRegion@@ABVUnknownObjectPair@@ABVMatrix3D@@ABUPoint2D@@ABVRect@@HI_NIII@Z=006d2810
// @ref ?Add@StaticBufferClass@@QAEPAUEntry@1@AAVSurface@@ABUSurfaceRegion@@@Z=0069a1d0
// @ref ?Blit_Voxel_006d29d0@TechnoClass@@QAEXPBXABUPoint2D@@ABVRect@@IH@Z=006d29d0
