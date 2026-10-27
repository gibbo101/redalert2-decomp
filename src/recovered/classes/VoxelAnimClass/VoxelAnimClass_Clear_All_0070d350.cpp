// void VoxelAnimClass::Clear_All() (0x0070D350)
// Deletes every voxel animation; each destructor takes itself off the list.
#include "shared/voxel_anim.hpp"

void __cdecl VoxelAnimClass::Clear_All()
{
    while (unknown_VoxelAnimClass_list_008399d0.Count() != 0) {
        delete unknown_VoxelAnimClass_list_008399d0[0];
    }
}
