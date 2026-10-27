// ?Rotate_Z@Matrix3D@@QAEXMM@Z (0x00590A40)
// Rotates about the local Z axis (sine and cosine given).
#include "shared/matrix3d.hpp"

void Matrix3D::Rotate_Z(float s, float c)
{
    float tmp1;
    float tmp2;
    tmp1 = Row[0][0];
    tmp2 = Row[0][1];
    Row[0][0] = c * tmp1 + s * tmp2;
    Row[0][1] = -s * tmp1 + c * tmp2;
    tmp1 = Row[1][0];
    tmp2 = Row[1][1];
    Row[1][0] = c * tmp1 + s * tmp2;
    Row[1][1] = -s * tmp1 + c * tmp2;
    tmp1 = Row[2][0];
    tmp2 = Row[2][1];
    Row[2][0] = c * tmp1 + s * tmp2;
    Row[2][1] = -s * tmp1 + c * tmp2;
}
