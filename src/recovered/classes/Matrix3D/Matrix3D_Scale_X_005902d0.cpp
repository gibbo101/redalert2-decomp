// ?Scale_X@Matrix3D@@QAEXM@Z (0x005902D0)
// Scales the local X axis.
#include "shared/matrix3d.hpp"

void Matrix3D::Scale_X(float x)
{
    Row[0][0] *= x; Row[1][0] *= x; Row[2][0] *= x;
}
