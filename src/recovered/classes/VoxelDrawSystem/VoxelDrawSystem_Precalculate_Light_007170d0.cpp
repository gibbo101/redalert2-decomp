// VoxelDrawSystem::Precalculate_Light with a viewer and specular strength (0x007170D0).
#include "shared/voxel_draw_system.hpp"

void __fastcall VoxelDrawSystem::Precalculate_Light(UnknownPairFirst *voxlib, int layer, int info, Matrix3D const &light_transform, Matrix3D const &view_transform, Vector3 const &light, float specular_strength)
{
    Matrix3D light_transform_inv = Matrix3D_Rigid_Inverse_00591420(light_transform);
    Matrix3D view_transform_inv = Matrix3D_Rigid_Inverse_00591420(view_transform);
    Vector3 light_tr = light_transform_inv.Rotate_Vector(light);
    Vector3 viewer_tr = view_transform_inv.Rotate_Vector(Vector3(0, 0, 1));
    int normal_type = voxlib->unknown_719860(layer, info)->unknown_a3;
    unknown_normal_lookup_71baa0(light_tr, viewer_tr, specular_strength, normal_type);
}
