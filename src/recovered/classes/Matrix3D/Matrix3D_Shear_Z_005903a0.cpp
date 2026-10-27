// ?Shear_Z@Matrix3D@@QAEXMM@Z (0x005903A0)
// Adds x times the X axis and y times the Y axis to the Z axis (name hypothesis).
#include "shared/matrix3d.hpp"

void Matrix3D::Shear_Z(float x, float y)
{
    Row[0][2] += Row[0][0] * x + Row[0][1] * y;
    Row[1][2] += Row[1][0] * x + Row[1][1] * y;
    Row[2][2] += Row[2][0] * x + Row[2][1] * y;
}
