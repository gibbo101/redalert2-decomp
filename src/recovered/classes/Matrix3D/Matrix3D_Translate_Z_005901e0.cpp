// ?Translate_Z@Matrix3D@@QAEXM@Z (0x005901E0)
// Moves the origin along the local Z axis.
#include "shared/matrix3d.hpp"

void Matrix3D::Translate_Z(float z)
{
    Row[0][3] += Row[0][2] * z;
    Row[1][3] += Row[1][2] * z;
    Row[2][3] += Row[2][2] * z;
}
