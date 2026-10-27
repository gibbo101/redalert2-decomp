// ?Get_Y_Translation@Matrix3D@@QBEMXZ (0x00590B10)
// The Y coordinate of the transformed origin.
#include "shared/matrix3d.hpp"
// @ref ??D@YI?AUVector3@@ABVMatrix3D@@ABU0@@Z=00591380

float Matrix3D::Get_Y_Translation() const
{
    Vector3 v = *this * Vector3(0.0f, 0.0f, 0.0f);
    return v.Y;
}
