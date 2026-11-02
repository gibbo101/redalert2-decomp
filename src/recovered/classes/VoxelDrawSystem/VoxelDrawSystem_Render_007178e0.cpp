// SurfaceRegion VoxelDrawSystem::Render() (0x007178E0; TibSun voxdrsys.cpp): the same draw as Render(Rect &, int &,
// int &) 0x007176C0, returning the drawn rectangle of the 256x256 buffer (padded by 4) and where its centre goes as
// one region. The padded rectangle is a named local whose Y stays in its home slot (frame 0x34).
#include "shared/voxel_draw_system.hpp"

SurfaceRegion __fastcall VoxelDrawSystem::Render()
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

    int width = unknown_bounds_max_ae0dd8.X - unknown_bounds_min_ae0a70.X;
    int height = unknown_bounds_max_ae0dd8.Y - unknown_bounds_min_ae0a70.Y;

    Rect rect;
    rect.X = 256 / 2 - width / 2;
    rect.Y = 256 / 2 - height / 2;
    width += 8;
    height += 8;
    rect.X -= 4;
    rect.Y -= 4;
    rect.Width = width;
    rect.Height = height;
    unknown_rect_ae2ff0 = rect;

    Point2D point;
    point.X = (int)center.X - width / 2;
    point.Y = (int)center.Y - height / 2;

    SurfaceRegion region;
    region.Point = point;
    region.Bounds = rect;
    return region;
}
