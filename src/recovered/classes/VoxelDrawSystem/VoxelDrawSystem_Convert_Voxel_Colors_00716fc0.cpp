// void VoxelDrawSystem::Convert_Voxel_Colors(int red_left, int red_right, int green_left, int green_right, int blue_left,
// int blue_right) (0x00716FC0; TibSun voxdrsys.cpp): converts the 256-entry voxel palette into screen pixels, each
// channel shifted right by its left count and left by its right count. The original walks a pointer to each entry's
// Green byte (red at -1, blue at +1) and the output pointer together; the TibSun index form gives a signed loop test.
// VoxelDrawSystem (Westwood voxdrsys.cpp as in Tiberian Sun; unit 0x00716D80-0x00717CDF): the voxel draw buffer
// (256x256, 8 bits) and its depth buffer, the per-frame object and shadow lists and their bounds, and the
// render that draws them centred in the buffer.
// @ref ?unknown_buffer_ae3408@@3PAEA=00ae3408
// @ref ?unknown_zbuffer_ad0a70@@3PAEA=00ad0a70
// @ref ?unknown_af6610@@3HA=00af6610
// @ref ?unknown_bounds_min_ae0a70@@3UVector3@@A=00ae0a70
// @ref ?unknown_bounds_max_ae0dd8@@3UVector3@@A=00ae0dd8
// @ref ?unknown_rect_ae2ff0@@3VRect@@A=00ae2ff0
// @ref ?unknown_records_ae0de8@@3PAUUnknownVoxelRecord88@@A=00ae0de8
// @ref ?unknown_records_af3408@@3PAUUnknownVoxelRecord48@@A=00af3408
// @ref ?unknown_voxel_colors_ae3008@@3PAVRGBClass@@A=00ae3008
// @ref ?unknown_voxel16_colors_ae0a7c@@3PAGA=00ae0a7c
// @ref ?unknown_voxel_record_count_ae0cb0@@3HA=00ae0cb0
// @ref ?unknown_voxel_shadow_count_ae3000@@3HA=00ae3000
// @ref _?_need_buffer_init@?1??Reset@VoxelDrawSystem@@YAXXZ@4HA=007f9d80
// @ref _?render_data@?1??Render@VoxelDrawSystem@@YIXAAVRect@@AAH1@Z@4PAPAUUnknownVoxelRecord88@@A=00ae3308
// @ref _?render_data@?1??Render@VoxelDrawSystem@@YI?AUSurfaceRegion@@XZ@4PAPAUUnknownVoxelRecord88@@A=00ae0cb4
// @ref ?unknown_719860@UnknownPairFirst@@QAEPAUUnknownVoxelTailer@@HH@Z=00719860
// @ref ?unknown_719940@UnknownPairFirst@@QAEXPAUUnknownVoxelDrawState@@PBUVector3@@@Z=00719940
// @ref ?unknown_719c10@UnknownPairFirst@@QAEXPAUUnknownVoxelRecord48@@PBUVector3@@@Z=00719c10
// @ref ??D@YI?AUVector3@@ABVMatrix3D@@ABU0@@Z=00591380
// @ref __real@4@3ffe8000000000000000=0079dd80
// @ref __ftol=0077f110
// @ref ?unknown_normal_lookup_71ba20@@YIXABUVector3@@H@Z=0071ba20
// @ref ?unknown_normal_lookup_71baa0@@YIXABUVector3@@0MH@Z=0071baa0
#define RA2_MATRIX3D_INLINE_COPY
#include "shared/vector3.hpp"
#include "shared/matrix3d.hpp"
#include "shared/rect.hpp"
#include "shared/rgb_class.hpp"
#include "shared/unknown_pair_first.hpp"
#include "shared/crt_memory.hpp"
#include "shared/voxel_draw_system.hpp"
#include "shared/voxel_render_record.hpp"

class Surface;


// The draw result of the second Render (0x18 bytes; TibSun SurfaceRegion): where to put the buffer's rectangle.
struct SurfaceRegion {
    Point2D Point;
    Rect Bounds;
};

extern unsigned char unknown_buffer_ae3408[256 * 256];      // 0x00AE3408 the draw buffer
extern unsigned char unknown_zbuffer_ad0a70[256 * 256];     // 0x00AD0A70 the depth buffer
extern int unknown_af6610;                                  // 0x00AF6610 depth buffering enabled
extern Vector3 unknown_bounds_min_ae0a70;                   // 0x00AE0A70
extern Vector3 unknown_bounds_max_ae0dd8;                   // 0x00AE0DD8
extern Rect unknown_rect_ae2ff0;                            // 0x00AE2FF0 the last rendered rectangle
extern UnknownVoxelRecord48 unknown_records_af3408[64];     // 0x00AF3408
extern RGBClass unknown_voxel_colors_ae3008[256];           // 0x00AE3008 the voxel palette
extern unsigned short unknown_voxel16_colors_ae0a7c[256];   // 0x00AE0A7C the palette in screen format
extern int unknown_voxel_record_count_ae0cb0;               // 0x00AE0CB0
extern int unknown_voxel_shadow_count_ae3000;               // 0x00AE3000

void __fastcall unknown_normal_lookup_71ba20(Vector3 const &light, int type);              // 0x0071BA20
void __fastcall unknown_normal_lookup_71baa0(Vector3 const &light, Vector3 const &viewer, float specular, int type);  // 0x0071BAA0

namespace VoxelDrawSystem {
    void __fastcall Convert_Voxel_Colors(int red_left, int red_right, int green_left, int green_right, int blue_left, int blue_right);
    unsigned char *Get_Surface_Buffer();
    void __fastcall Precalculate_Light(UnknownPairFirst *voxlib, int layer, int info, Matrix3D const &light_transform, Vector3 const &light);
    void __fastcall Precalculate_Light(UnknownPairFirst *voxlib, int layer, int info, Matrix3D const &light_transform, Matrix3D const &view_transform, Vector3 const &light, float specular_strength);
    void Reset();
    void __fastcall Prep_For_Shadow(UnknownPairFirst *voxlib, int layer, int info, Matrix3D const &camera, Matrix3D const &motion, Vector3 const &light, Surface *mask, int mask_x, int mask_y);
    void __fastcall Prep_For_Object(UnknownPairFirst *voxlib, int layer, int info, Matrix3D const &transform);
    void __fastcall Render(Rect &rect, int &x, int &y);
    SurfaceRegion __fastcall Render();
    void Clear_Buffer();
    void __fastcall Clear_Buffer(Rect &region);
    void Clear_Z_Buffer();
    void __fastcall Clear_Z_Buffer(int x, int y, int width, int height);
}

void __fastcall VoxelDrawSystem::Convert_Voxel_Colors(int red_left, int red_right, int green_left, int green_right, int blue_left, int blue_right)
{
    unsigned short *out = unknown_voxel16_colors_ae0a7c;
    for (unsigned char const *channel = &unknown_voxel_colors_ae3008[0].Green; channel < &unknown_voxel_colors_ae3008[256].Green; channel += sizeof(RGBClass)) {
        unsigned char red = channel[-1];
        unsigned char green = channel[0];
        unsigned char blue = channel[1];
        *out++ = (((red >> red_left) << red_right) | ((green >> green_left) << green_right) | ((blue >> blue_left) << blue_right));
    }
}
