// ?Shear_X@Matrix3D@@QAEXMM@Z (0x00590350)
// Adds y times the Y axis and z times the Z axis to the X axis (name hypothesis).
#include "shared/matrix3d.hpp"

void Matrix3D::Shear_X(float y, float z)
{
    Row[0][0] += Row[0][1] * y + Row[0][2] * z;
    Row[1][0] += Row[1][1] * y + Row[1][2] * z;
    Row[2][0] += Row[2][1] * y + Row[2][2] * z;
}
