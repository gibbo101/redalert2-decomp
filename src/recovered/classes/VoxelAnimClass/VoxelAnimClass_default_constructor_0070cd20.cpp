// VoxelAnimClass::VoxelAnimClass() (0x0070CD20)
// An empty voxel animation registered in the voxel animation list.
#include "shared/voxel_anim.hpp"
// @ref ??0ObjectClass@@QAE@XZ=005d22e0
// @ref ??0UnknownQuaternion@@QAE@MMMM@Z=00622160
// @ref ?Create_ID@AbstractClass@@UAGXXZ=0040ffd0
// @ref ?Init@UnknownAudioController@@QAEXXZ=00405bf0
// @ref ?unknown_VoxelAnimClass_list_008399d0@@3V?$DynamicVectorClass@PAVVoxelAnimClass@@@@A=008399d0
// @ref ??_7VoxelAnimClass@@6BIPersistStream@@@=007ae428
// @ref ??_7VoxelAnimClass@@6BIRTTITypeInfo@@@=007ae40c
// @ref ??_7VoxelAnimClass@@6BINoticeSink@@@=007ae404
// @ref ??_7VoxelAnimClass@@6BINoticeSource@@@=007ae3fc

VoxelAnimClass::VoxelAnimClass() :
    unknown_e8(-1),
    Class(0),
    unknown_f0(0),
    unknown_f4(0),
    unknown_f8(false),
    unknown_124(false),
    unknown_128(0)
{
    AbstractClass::Create_ID();
    unknown_fc.Init();
    unknown_110.Init();
    unknown_VoxelAnimClass_list_008399d0.Add(this);
}
