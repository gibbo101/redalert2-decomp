// ?Rotate_Y@Matrix3D@@QAEXMM@Z (0x00590920)
// Rotates about the local Y axis (sine and cosine given).
#include "shared/matrix3d.hpp"

void Matrix3D::Rotate_Y(float s, float c)
{
    float tmp1;
    float tmp2;
    tmp1 = Row[0][0];
    tmp2 = Row[0][2];
    Row[0][0] = c * tmp1 - s * tmp2;
    Row[0][2] = s * tmp1 + c * tmp2;
    tmp1 = Row[1][0];
    tmp2 = Row[1][2];
    Row[1][0] = c * tmp1 - s * tmp2;
    Row[1][2] = s * tmp1 + c * tmp2;
    tmp1 = Row[2][0];
    tmp2 = Row[2][2];
    Row[2][0] = c * tmp1 - s * tmp2;
    Row[2][2] = s * tmp1 + c * tmp2;
}
