// ?Translate@Matrix3D@@QAEXMMM@Z (0x00590090)
// Moves the origin by (x, y, z) in local coordinates.
#include "shared/matrix3d.hpp"

void Matrix3D::Translate(float x, float y, float z)
{
    Row[0][3] += Row[0][0] * x + Row[0][1] * y + Row[0][2] * z;
    Row[1][3] += Row[1][0] * x + Row[1][1] * y + Row[1][2] * z;
    Row[2][3] += Row[2][0] * x + Row[2][1] * y + Row[2][2] * z;
}
