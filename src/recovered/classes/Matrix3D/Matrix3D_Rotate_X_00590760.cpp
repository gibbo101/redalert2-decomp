// ?Rotate_X@Matrix3D@@QAEXM@Z (0x00590760)
// Rotates about the local X axis by theta.
#include "shared/matrix3d.hpp"
// @ref ?Fast_Sin@@YAMN@Z=004ba480
// @ref ?Fast_Cos@@YAMN@Z=004ba4d0

void Matrix3D::Rotate_X(float theta)
{
    float s = Fast_Sin(theta);
    float c = Fast_Cos(theta);
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
