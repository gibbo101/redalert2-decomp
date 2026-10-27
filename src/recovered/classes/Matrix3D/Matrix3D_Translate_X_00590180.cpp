// ?Translate_X@Matrix3D@@QAEXM@Z (0x00590180)
// Moves the origin along the local X axis.
#include "shared/matrix3d.hpp"

void Matrix3D::Translate_X(float x)
{
    Row[0][3] += Row[0][0] * x;
    Row[1][3] += Row[1][0] * x;
    Row[2][3] += Row[2][0] * x;
}
