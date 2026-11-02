// VoxelDrawSystem::Reset (0x007171D0): empties the lists, clears the buffers (all of them the first time, then the
// last rendered rectangle) and resets the bounds.
#include "shared/voxel_draw_system.hpp"

void VoxelDrawSystem::Reset()
{
    static int _need_buffer_init = true;

    unknown_voxel_record_count_ae0cb0 = 0;
    unknown_voxel_shadow_count_ae3000 = 0;

    if (_need_buffer_init) {
        Clear_Buffer();
        Clear_Z_Buffer();
        _need_buffer_init = false;
    } else {
        if (unknown_rect_ae2ff0.X >= 0 && unknown_rect_ae2ff0.Y >= 0 && unknown_rect_ae2ff0.X + unknown_rect_ae2ff0.Width <= 255 && unknown_rect_ae2ff0.Y + unknown_rect_ae2ff0.Height <= 255) {
            for (int i = unknown_rect_ae2ff0.Y; i <= unknown_rect_ae2ff0.Y + unknown_rect_ae2ff0.Height; i++) {
                memset(&unknown_buffer_ae3408[256 * i + unknown_rect_ae2ff0.X], 0, unknown_rect_ae2ff0.Width + 1);
            }
        } else {
            memset(unknown_buffer_ae3408, 0, sizeof(unknown_buffer_ae3408));
        }
        if (unknown_af6610) {
            if (unknown_rect_ae2ff0.Y <= unknown_rect_ae2ff0.Height + unknown_rect_ae2ff0.Y) {
                for (int i = unknown_rect_ae2ff0.Y; i <= unknown_rect_ae2ff0.Y + unknown_rect_ae2ff0.Height; i++) {
                    memset(&unknown_zbuffer_ad0a70[256 * i + unknown_rect_ae2ff0.X], 0, unknown_rect_ae2ff0.Width + 1);
                }
            }
        }
    }

    unknown_bounds_min_ae0a70 = Vector3(10000, 10000, 10000);
    unknown_bounds_max_ae0dd8 = Vector3(-10000, -10000, -10000);
}
