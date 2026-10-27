// ?Translate@Matrix3D@@QAEXABUVector3@@@Z (0x005900F0)
// Moves the origin by offset in local coordinates: Translate_X, _Y and _Z (defined later, expanded inline).
#include "shared/matrix3d.hpp"

void Matrix3D::Translate(Vector3 const &offset)
{
    Translate_X(offset.X);
    Translate_Y(offset.Y);
    Translate_Z(offset.Z);
}
