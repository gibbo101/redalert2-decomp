// VoxelDrawSystem::Precalculate_Light (0x00717050): the light in the section's frame, then the normal lookup for the
// section's normal table (TibSun voxdrsys.cpp).
#include "shared/voxel_draw_system.hpp"

void __fastcall VoxelDrawSystem::Precalculate_Light(UnknownPairFirst *voxlib, int layer, int info, Matrix3D const &light_transform, Vector3 const &light)
{
    Matrix3D light_transform_inv = Matrix3D_Rigid_Inverse_00591420(light_transform);
    Vector3 light_tr = light_transform_inv.Rotate_Vector(light);
    int normal_type = voxlib->unknown_719860(layer, info)->unknown_a3;
    unknown_normal_lookup_71ba20(light_tr, normal_type);
}
