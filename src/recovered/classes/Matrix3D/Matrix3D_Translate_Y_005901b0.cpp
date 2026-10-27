// ?Translate_Y@Matrix3D@@QAEXM@Z (0x005901B0)
// Moves the origin along the local Y axis.
#include "shared/matrix3d.hpp"

void Matrix3D::Translate_Y(float y)
{
    Row[0][3] += Row[0][1] * y;
    Row[1][3] += Row[1][1] * y;
    Row[2][3] += Row[2][1] * y;
}
