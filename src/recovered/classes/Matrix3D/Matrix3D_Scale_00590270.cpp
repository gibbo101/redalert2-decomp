// ?Scale@Matrix3D@@QAEXMMM@Z (0x00590270)
// Scales the axes by x, y and z.
#include "shared/matrix3d.hpp"

void Matrix3D::Scale(float x, float y, float z)
{
    Row[0][0] *= x; Row[1][0] *= x; Row[2][0] *= x;
    Row[0][1] *= y; Row[1][1] *= y; Row[2][1] *= y;
    Row[0][2] *= z; Row[1][2] *= z; Row[2][2] *= z;
}
