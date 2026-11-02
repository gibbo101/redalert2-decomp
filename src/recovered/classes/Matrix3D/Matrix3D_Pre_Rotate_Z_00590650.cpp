// ?Pre_Rotate_Z@Matrix3D@@QAEXM@Z (0x00590650)
// Rotates about the world Z axis by theta (rows 0 and 1 mixed).
#include "shared/matrix3d.hpp"
// @ref ?Fast_Sin@@YAMN@Z=004ba480
// @ref ?Fast_Cos@@YAMN@Z=004ba4d0

void Matrix3D::Pre_Rotate_Z(float theta)
{
    float s = Fast_Sin(theta);
    float c = Fast_Cos(theta);
    float ns = -s;
    float a0 = Row[0][0];
    float a1 = Row[0][1];
    float a2 = Row[0][2];
    float a3 = Row[0][3];
    float b0 = Row[1][0];
    float b1 = Row[1][1];
    float b2 = Row[1][2];
    float b3 = Row[1][3];
    Row[0][0] = c * a0 + ns * b0;
    Row[0][1] = c * a1 + ns * b1;
    Row[0][2] = c * a2 + ns * b2;
    Row[0][3] = c * a3 + ns * b3;
    Row[1][0] = s * a0 + c * b0;
    Row[1][1] = s * a1 + c * b1;
    Row[1][2] = s * a2 + c * b2;
    Row[1][3] = s * a3 + c * b3;
}
