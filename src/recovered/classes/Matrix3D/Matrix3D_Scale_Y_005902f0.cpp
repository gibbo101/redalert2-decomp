// ?Scale_Y@Matrix3D@@QAEXM@Z (0x005902F0)
// Scales the local Y axis.
#include "shared/matrix3d.hpp"

void Matrix3D::Scale_Y(float y)
{
    Row[0][1] *= y; Row[1][1] *= y; Row[2][1] *= y;
}
