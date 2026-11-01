// BounceClass (TibSun bounce.cpp, unit 0x00436A80): the bouncing motion of debris
// (AnimClass +0x108, VoxelAnimClass +0x98). void BounceClass::Init(CoordStruct const &,
// double elasticity, double gravity, double max_velocity, Vector3 const &velocity,
// double rotation) (0x00436DC0): starts the bounce with a random tumble axis.
#define RA2_BOUNCE_DECLARE_MEMBERS
#define RA2_VECTOR3_DECLARE_LENGTH
#define RA2_TPOINT3D_LENGTH
#define RA2_MATRIX3D_INLINE_COPY
#include "shared/bounce.hpp"
#include "shared/id_source.hpp"
#include "shared/unknown_geometry.hpp"

// TibSun vector3.h's scalar division and Normalize; Length2 reads the components into
// locals (X, Z, Y: the order the stored components are reloaded), and Normalize writes
// Length out (the unit's Vector3::Length 0x00437710 is out of line).
inline Vector3 operator/(Vector3 const &a, double k)
{
    return Vector3((float)(a.X / k), (float)(a.Y / k), (float)(a.Z / k));
}

inline float Length2(Vector3 const &vec)
{
    float x = vec.X;
    float z = vec.Z;
    float y = vec.Y;
    return x * x + y * y + z * z;
}

inline Vector3 Normalize(Vector3 const &vec)
{
    float len = (float)unknown_sqrt_4ba410(Length2(vec));
    if (len != 0.0) {
        return vec / len;
    }
    return vec;
}

void BounceClass::Init(CoordStruct const &coord, double elasticity, double gravity, double max_velocity,
                       Vector3 const &velocity, double rotation)
{
    unknown_00.unknown_00 = elasticity;
    unknown_00.unknown_08 = gravity;
    unknown_00.unknown_10 = max_velocity;
    unknown_00.Position.X = coord.X;
    unknown_00.Position.Y = coord.Y;
    unknown_00.Position.Z = coord.Z;
    *(Vector3 *)unknown_00.unknown_24 = velocity;

    Vector3 rotation_axis(
        Random_Pick(-65535, 65535) * (1.0f / 65535.0f),
        Random_Pick(-65535, 65535) * (1.0f / 65535.0f),
        Random_Pick(-65535, 65535) * (1.0f / 65535.0f));

    rotation_axis = Normalize(rotation_axis);
    (Quaternion &)unknown_40 = Axis_To_Quat(rotation_axis, rotation);
    Matrix3D identity_matrix;
    identity_matrix.Make_Identity();
    (Quaternion &)unknown_30 = Build_Quaternion(identity_matrix);
}
// @ref ??4Quaternion@@QAE?AV0@ABV0@@Z=00622250
// @ref ??RRandom2Class@@QAEHHH@Z=006388a0
// @ref ?Axis_To_Quat@@YI?AVQuaternion@@ABUVector3@@M@Z=006229b0
// @ref ?Build_Quaternion@@YI?AVQuaternion@@ABVMatrix3D@@@Z=00622c60
// @ref ?Make_Identity@Matrix3D@@QAEXXZ=00590060
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref __real@4@3fef8000800000000000=0079ca90
// @ref __real@8@00000000000000000000=0079b610
