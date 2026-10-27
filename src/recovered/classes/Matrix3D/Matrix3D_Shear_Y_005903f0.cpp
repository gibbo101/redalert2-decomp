// ?Shear_Y@Matrix3D@@QAEXMM@Z (0x005903F0)
// Adds x times the X axis and z times the Z axis to the Y axis (name hypothesis).
#include "shared/matrix3d.hpp"

void Matrix3D::Shear_Y(float x, float z)
{
    Row[0][1] += Row[0][0] * x + Row[0][2] * z;
    Row[1][1] += Row[1][0] * x + Row[1][2] * z;
    Row[2][1] += Row[2][0] * x + Row[2][2] * z;
}
