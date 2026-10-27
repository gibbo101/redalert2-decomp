// ?Scale@Matrix3D@@QAEXM@Z (0x00590210)
// Scales the three axes by scale.
#include "shared/matrix3d.hpp"

void Matrix3D::Scale(float scale)
{
    Row[0][0] *= scale; Row[1][0] *= scale; Row[2][0] *= scale;
    Row[0][1] *= scale; Row[1][1] *= scale; Row[2][1] *= scale;
    Row[0][2] *= scale; Row[1][2] *= scale; Row[2][2] *= scale;
}
