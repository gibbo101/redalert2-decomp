// Matrix3D::Matrix3D(float unknown1, float unknown2) (0x0058FEF0)
// Identity rotated about Z by unknown1, about X by unknown2 and back about Z
// by -unknown1 (a tilt of unknown2 towards direction unknown1; meaning of the
// parameters is a hypothesis).
#include "shared/matrix3d.hpp"
// @ref ?Rotate_Z@Matrix3D@@QAEXM@Z=005909a0
// @ref ?Rotate_X@Matrix3D@@QAEXM@Z=00590760

Matrix3D::Matrix3D(float unknown1, float unknown2)
{
    Make_Identity();
    Rotate_Z(unknown1);
    Rotate_X(unknown2);
    Rotate_Z(-unknown1);
}
