// VoxelDrawSystem::Clear_Z_Buffer() (0x00717C10)
#include "shared/voxel_draw_system.hpp"

void VoxelDrawSystem::Clear_Z_Buffer()
{
    memset(unknown_zbuffer_ad0a70, 0, sizeof(unknown_zbuffer_ad0a70));
}
