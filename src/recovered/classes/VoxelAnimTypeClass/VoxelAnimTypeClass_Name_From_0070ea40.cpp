// VoxelAnimTypeClass Name_From0070EA40: unsigned lookup, preserving the original upper-bound test.
#define VECTOR_IMPLEMENT_ALL
#define VOXEL_ANIM_TYPE_DECLARE_NAME_FROM
#include "shared/voxel_anim_type.hpp"
// @ref ??_C@_00A@?$AA@=0083c55c
// @ref ?VoxelAnimTypes@@3V?$DynamicVectorClass@PAVVoxelAnimTypeClass@@@@A=00a40ae0
char const *__fastcall VoxelAnimTypeClass::Name_From(unsigned index)
{
    if (index > (unsigned)VoxelAnimTypes.Count()) return "";
    return VoxelAnimTypes[index]->ID;
}
