// VoxelDrawSystem::Clear_Buffer() (0x00717AF0)
#include "shared/voxel_draw_system.hpp"

void VoxelDrawSystem::Clear_Buffer()
{
    memset(unknown_buffer_ae3408, 0, sizeof(unknown_buffer_ae3408));
}
