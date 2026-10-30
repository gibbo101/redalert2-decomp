// The .VXL voxel library (UnknownPairFirst, 0x00719060-0x0071BCD6) and the
// voxel palette lookup (UnknownVoxelPalette, 0x0071BD00-0x0071C314). The unit's
// only dynamic initializer (0x00719040) is shared/unknown_static_rect.hpp's.
#include "shared/unknown_static_rect.hpp"
#include "shared/unknown_pair_first.hpp"
#include "shared/unknown_voxel_palette.hpp"
#include "shared/raw_file_class.hpp"
#include "shared/fast_math.hpp"
#include "shared/crt_memory.hpp"
// @ref _unknown_static_rect=00af8a00
// @ref ?unknown_levels_af8f10@@3PAMA=00af8f10
// @ref __real@4@3ffb8000000000000000=007a7b20
// @ref __real@4@3ffecccccd0000000000=007aea4c
// @ref __real@4@3ffe999999a000000000=007aea48
// @ref __real@4@3ffdccccccd000000000=007a7b18
// @ref __real@4@4006ff00000000000000=0079b0a8
// @ref __real@4@00000000000000000000=0079a738
// @ref ?unknown_views_7f9e60@@3PAUUnknownVoxelView@@A=007f9e60
// @ref ?unknown_drawers_7f9de0@@3PAP6AXPAUVoxelFuncArgumentStruct@@@ZA=007f9de0
// @ref ?unknown_af6610@@3HA=00af6610
// @ref ?unknown_af6614@@3HA=00af6614
// @ref __real@4@40068000000000000000=007aea3c
// @ref __real@4@40078000000000000000=0079b0ac
// @ref ?unknown_steps_af8a10@@3PAY01FA=00af8a10
// @ref ?unknown_grid_ae3408@@3PAEA=00ae3408
// @ref ??2@YAPAXI@Z=00782017
// @ref ??3@YAXPAX@Z=00781d3b
// @ref __ftol=0077f110
// @ref ?Fast_Sqrt@@YAMN@Z=004ba410
// @ref ?unknown_719160@UnknownPairFirst@@QAEHPAVFileClass@@H@Z=00719160
// @ref ?unknown_71c250@UnknownVoxelPalette@@QAEEMMM_N@Z=0071c250
// @ref ?unknown_normal_tables_7f9f80@@3PAPBUVector3@@A=007f9f80
// @ref ?unknown_normal_counts_7f9f94@@3PAHA=007f9f94
// @ref ?unknown_shades_af8e10@@3PAEA=00af8e10
// @ref __real@4@3ffe8000000000000000=0079dd80
// @ref __real@4@3ffccccccd0000000000=007aea44
// @ref __real@4@40038000000000000000=007aea40
// @ref __real@8@00000000000000000000=0079b610

// Three unsigned shorts (8.8 fixed-point screen steps; TibSun's Vector3i16).
struct Vector3i16 {
    unsigned short I;
    unsigned short J;
    unsigned short K;
};

// The span drawer's parameters (0x34 bytes; TibSun's VoxelFuncArgumentStruct,
// names hypotheses).
struct VoxelFuncArgumentStruct {
    int *StartOffset;                   // the tailer's span start offsets
    int *EndOffset;                     // span end offsets
    unsigned char *DataOffset;          // span data
    int StartIndex;                     // current column
    int StrideX;
    int StrideY;
    Vector3i16 TransformMatrix[4];      // origin, x, y and z steps
    unsigned char XSize;                // +0x30
    unsigned char YSize;
    unsigned char ZSize;
};

// Per view: the drawer flags, the origin corner and the x/y/z edge corners
// (indexes into the 8 box corners) and four span strides.
struct UnknownVoxelView {
    int unknown_00;
    int unknown_04;
    int unknown_08;
    int unknown_0c;
    int unknown_10;
    int unknown_14;
    int unknown_18;
    int unknown_1c;
    int unknown_20;
};

extern UnknownVoxelView unknown_views_7f9e60[];
extern void (*unknown_drawers_7f9de0[])(VoxelFuncArgumentStruct *parameters);
extern int unknown_af6610;
extern int unknown_af6614;

// The screen offsets per depth (8.8 fixed point x/y) of the span drawers.
short unknown_steps_af8a10[256][2];

// The 256x256 byte grid the span drawers write (another unit's).
extern unsigned char unknown_grid_ae3408[];

// The normal vector tables per normal type (0 none) and their sizes.
extern Vector3 const *unknown_normal_tables_7f9f80[5];
extern int unknown_normal_counts_7f9f94[5];

// The default brightness levels of UnknownVoxelPalette::unknown_71bf20.
float unknown_levels_af8f10[32];

// The shade per normal (0x10 is unlit).
unsigned char unknown_shades_af8e10[256];
