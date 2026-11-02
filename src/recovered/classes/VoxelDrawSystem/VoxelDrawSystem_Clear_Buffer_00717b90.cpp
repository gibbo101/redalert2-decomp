// VoxelDrawSystem::Clear_Buffer(Rect &) (0x00717B90): the rectangle's rows (one more column), or all of it when
// the rectangle leaves the buffer.
#include "shared/voxel_draw_system.hpp"

void __fastcall VoxelDrawSystem::Clear_Buffer(Rect &region)
{
    if (region.X >= 0 && region.Y >= 0 && region.X + region.Width <= 255 && region.Y + region.Height <= 255) {
        for (int i = region.Y; i <= region.Y + region.Height; i++) {
            memset(&unknown_buffer_ae3408[256 * i + region.X], 0, region.Width + 1);
        }
    } else {
        memset(unknown_buffer_ae3408, 0, sizeof(unknown_buffer_ae3408));
    }
}
