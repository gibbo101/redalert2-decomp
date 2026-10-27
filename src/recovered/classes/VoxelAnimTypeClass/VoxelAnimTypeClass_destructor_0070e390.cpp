// VoxelAnimTypeClass::~VoxelAnimTypeClass() (0x0070E390)
// Leaves both lists; a borrowed (shared) voxel pair is released without
// being destroyed.
#include "shared/voxel_anim_type.hpp"
// @ref ?Unknown_006ECB90@@YIXPAVAbstractClass@@_N@Z=006ecb90
// @ref ??1ObjectTypeClass@@UAE@XZ=005d5b60

VoxelAnimTypeClass::~VoxelAnimTypeClass()
{
    Unknown_006ECB90(this, true);
    unknown_objects_ac0cb0.Delete(this);
    VoxelAnimTypes.Delete(this);
    if (unknown_266) {
        unknown_b0.unknown_00 = 0;
        unknown_b0.unknown_04 = 0;
    }
}
