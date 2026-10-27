// ?Scale_Z@Matrix3D@@QAEXM@Z (0x00590320)
// Scales the local Z axis.
#include "shared/matrix3d.hpp"

void Matrix3D::Scale_Z(float z)
{
    Row[0][2] *= z; Row[1][2] *= z; Row[2][2] *= z;
}
