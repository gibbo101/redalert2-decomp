// VoxelDrawSystem::Render(Rect &rect, int &x, int &y) (0x007176C0; TibSun voxdrsys.cpp): draws the queued shadows,
// then the queued objects sorted by their far Z (back to front, or front to back with the depth buffer), and
// returns the drawn rectangle of the 256x256 buffer (padded by 4) and where its centre goes.
#include "shared/voxel_draw_system.hpp"

void __fastcall VoxelDrawSystem::Render(Rect &rect, int &x, int &y)
{
    static UnknownVoxelRecord88 *render_data[64];

    int index;

    Vector3 center;
    center.X = (unknown_bounds_max_ae0dd8.X + unknown_bounds_min_ae0a70.X) * 0.5f;
    center.Y = (unknown_bounds_max_ae0dd8.Y + unknown_bounds_min_ae0a70.Y) * 0.5f;
    center.Z = (unknown_bounds_max_ae0dd8.Z + unknown_bounds_min_ae0a70.Z) * 0.5f;

    for (index = 0; index < unknown_voxel_shadow_count_ae3000; index++) {
        unknown_records_af3408[index].unknown_00->unknown_719c10(&unknown_records_af3408[index], &center);
    }

    for (index = 0; index < unknown_voxel_record_count_ae0cb0; index++) {
        render_data[index] = &unknown_records_ae0de8[index];
    }

    for (index = 0; index < unknown_voxel_record_count_ae0cb0 - 1; index++) {
        for (int index2 = index + 1; index2 < unknown_voxel_record_count_ae0cb0; index2++) {
            UnknownVoxelRecord88 *first = render_data[index];
            UnknownVoxelRecord88 *second = render_data[index2];

            if (first->MaxBounds.Z > second->MaxBounds.Z) {
                render_data[index] = second;
                render_data[index2] = first;
            }
        }
    }

    if (unknown_af6610) {
        for (index = unknown_voxel_record_count_ae0cb0 - 1; index >= 0; index--) {
            render_data[index]->Library->unknown_719940((UnknownVoxelDrawState *)render_data[index], &center);
        }
    } else {
        for (index = 0; index < unknown_voxel_record_count_ae0cb0; index++) {
            render_data[index]->Library->unknown_719940((UnknownVoxelDrawState *)render_data[index], &center);
        }
    }

    rect.Width = unknown_bounds_max_ae0dd8.X - unknown_bounds_min_ae0a70.X;

    rect.Height = unknown_bounds_max_ae0dd8.Y - unknown_bounds_min_ae0a70.Y;

    rect.Set(256 / 2 - rect.Width / 2, 256 / 2 - rect.Height / 2, rect.Width + 8, rect.Height + 8);

    rect.X -= 4;
    rect.Y -= 4;
    unknown_rect_ae2ff0 = rect;

    x = (int)center.X - rect.Width / 2;
    y = (int)center.Y - rect.Height / 2;
}
