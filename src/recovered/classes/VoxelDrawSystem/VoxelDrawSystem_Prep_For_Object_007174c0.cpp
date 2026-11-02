// VoxelDrawSystem::Prep_For_Object (0x007174C0): queues a section with its transformed box and bounds.
#include "shared/voxel_draw_system.hpp"

void __fastcall VoxelDrawSystem::Prep_For_Object(UnknownPairFirst *voxlib, int layer, int info, Matrix3D const &transform)
{
    UnknownVoxelTailer const *layer_info = voxlib->unknown_719860(layer, info);

    UnknownVoxelRecord88 &data = unknown_records_ae0de8[unknown_voxel_record_count_ae0cb0];

    data.MinBounds = Vector3(10000, 10000, 10000);
    data.MaxBounds = Vector3(-10000, -10000, -10000);
    data.Frame = info;
    data.Section = layer;
    data.Library = voxlib;

    for (int i = 0; i < 8; i++) {
        data.Points[i] = transform * layer_info->unknown_40[i];
        data.Points[i].Y = -data.Points[i].Y;
        if (data.Points[i].X < data.MinBounds.X) {
            data.MinBounds.X = data.Points[i].X;
        }
        if (data.Points[i].X > data.MaxBounds.X) {
            data.MaxBounds.X = data.Points[i].X;
        }
        if (data.Points[i].Y < data.MinBounds.Y) {
            data.MinBounds.Y = data.Points[i].Y;
        }
        if (data.Points[i].Y > data.MaxBounds.Y) {
            data.MaxBounds.Y = data.Points[i].Y;
        }
        if (data.Points[i].Z < data.MinBounds.Z) {
            data.MinBounds.Z = data.Points[i].Z;
            data.AnchorCorner = i;
        }
        if (data.Points[i].Z > data.MaxBounds.Z) {
            data.MaxBounds.Z = data.Points[i].Z;
        }
    }

    if (data.MinBounds.X < unknown_bounds_min_ae0a70.X) {
        unknown_bounds_min_ae0a70.X = data.MinBounds.X;
    }
    if (data.MinBounds.Y < unknown_bounds_min_ae0a70.Y) {
        unknown_bounds_min_ae0a70.Y = data.MinBounds.Y;
    }
    if (data.MinBounds.Z < unknown_bounds_min_ae0a70.Z) {
        unknown_bounds_min_ae0a70.Z = data.MinBounds.Z;
    }
    if (data.MaxBounds.X > unknown_bounds_max_ae0dd8.X) {
        unknown_bounds_max_ae0dd8.X = data.MaxBounds.X;
    }
    if (data.MaxBounds.Y > unknown_bounds_max_ae0dd8.Y) {
        unknown_bounds_max_ae0dd8.Y = data.MaxBounds.Y;
    }
    if (data.MaxBounds.Z > unknown_bounds_max_ae0dd8.Z) {
        unknown_bounds_max_ae0dd8.Z = data.MaxBounds.Z;
    }

    unknown_voxel_record_count_ae0cb0++;
}
