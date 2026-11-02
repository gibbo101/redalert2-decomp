// VoxelDrawSystem::Clear_Z_Buffer(int x, int y, int width, int height) (0x00717C30)
#include "shared/voxel_draw_system.hpp"

void __fastcall VoxelDrawSystem::Clear_Z_Buffer(int x, int y, int width, int height)
{
    for (int i = y; i <= y + height; i++) {
        memset(&unknown_zbuffer_ad0a70[256 * i + x], 0, width);
    }
}
