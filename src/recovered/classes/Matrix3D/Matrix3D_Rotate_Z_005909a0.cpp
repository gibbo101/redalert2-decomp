// ?Rotate_Z@Matrix3D@@QAEXM@Z (0x005909A0)
// Rotates about the local Z axis by theta.
#include "shared/matrix3d.hpp"
// @ref ?Fast_Sin@@YAMN@Z=004ba480
// @ref ?Fast_Cos@@YAMN@Z=004ba4d0

void Matrix3D::Rotate_Z(float theta)
{
    float c = Fast_Cos(theta);
    float s = Fast_Sin(theta);
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
