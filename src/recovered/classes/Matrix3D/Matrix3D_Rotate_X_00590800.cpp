// ?Rotate_X@Matrix3D@@QAEXMM@Z (0x00590800)
// Rotates about the local X axis (sine and cosine given).
#include "shared/matrix3d.hpp"

void Matrix3D::Rotate_X(float s, float c)
{
    float tmp1;
    float tmp2;
    tmp1 = Row[0][1];
    tmp2 = Row[0][2];
    Row[0][1] = c * tmp1 + s * tmp2;
    Row[0][2] = -s * tmp1 + c * tmp2;
    tmp1 = Row[1][1];
    tmp2 = Row[1][2];
    Row[1][1] = c * tmp1 + s * tmp2;
    Row[1][2] = -s * tmp1 + c * tmp2;
    tmp1 = Row[2][1];
    tmp2 = Row[2][2];
    Row[2][1] = c * tmp1 + s * tmp2;
    Row[2][2] = -s * tmp1 + c * tmp2;
}
