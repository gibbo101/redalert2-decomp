// ?Get_Z_Translation@Matrix3D@@QBEMXZ (0x00590B60)
// The Z coordinate of the transformed origin.
#include "shared/matrix3d.hpp"
// @ref ??D@YI?AUVector3@@ABVMatrix3D@@ABU0@@Z=00591380

float Matrix3D::Get_Z_Translation() const
{
    Vector3 v = *this * Vector3(0.0f, 0.0f, 0.0f);
    return v.Z;
}
