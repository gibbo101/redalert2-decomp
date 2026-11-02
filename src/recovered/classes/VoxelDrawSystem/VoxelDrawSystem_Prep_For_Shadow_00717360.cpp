// VoxelDrawSystem::Prep_For_Shadow (0x00717360): queues a section's shadow (its four ground corners; RA2 adds the
// mask surface and offset) and grows the bounds.
#include "shared/voxel_draw_system.hpp"

void __fastcall VoxelDrawSystem::Prep_For_Shadow(UnknownPairFirst *voxlib, int layer, int info, Matrix3D const &camera, Matrix3D const &motion, Vector3 const &light, Surface *mask, int mask_x, int mask_y)
{
    UnknownVoxelTailer const *layer_info = voxlib->unknown_719860(layer, info);

    UnknownVoxelRecord48 &data = unknown_records_af3408[unknown_voxel_shadow_count_ae3000];

    data.unknown_3c = mask;
    data.unknown_40 = mask_x;
    data.unknown_44 = mask_y;
    data.unknown_00 = voxlib;
    data.unknown_04 = layer;
    data.unknown_08 = info;

    for (int i = 0; i < 4; i++) {
        data.Points[i] = motion * layer_info->unknown_40[i];
        data.Points[i].Z = 0;
        data.Points[i] = camera * data.Points[i];
        data.Points[i] = data.Points[i] + light;
        data.Points[i].Y = -data.Points[i].Y;

        if (data.Points[i].X < unknown_bounds_min_ae0a70.X) {
            unknown_bounds_min_ae0a70.X = data.Points[i].X;
        }
        if (data.Points[i].Y < unknown_bounds_min_ae0a70.Y) {
            unknown_bounds_min_ae0a70.Y = data.Points[i].Y;
        }
        if (data.Points[i].X > unknown_bounds_max_ae0dd8.X) {
            unknown_bounds_max_ae0dd8.X = data.Points[i].X;
        }
        if (data.Points[i].Y > unknown_bounds_max_ae0dd8.Y) {
            unknown_bounds_max_ae0dd8.Y = data.Points[i].Y;
        }
    }

    unknown_voxel_shadow_count_ae3000++;
}
