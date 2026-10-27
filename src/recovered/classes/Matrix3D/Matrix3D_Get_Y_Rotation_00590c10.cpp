// ?Get_Y_Rotation@Matrix3D@@QBEMXZ (0x00590C10)
// The rotation about the Y axis, from where the transform takes a unit axis.
#include "shared/matrix3d.hpp"
// @ref ??D@YI?AUVector3@@ABVMatrix3D@@ABU0@@Z=00591380
// @ref ?Fast_Atan2@@YAMNN@Z=004ba600

float Matrix3D::Get_Y_Rotation() const
{
    Vector3 v = *this * Vector3(0.0f, 0.0f, 1.0f);
    return Fast_Atan2(v.X, v.Z);
}
