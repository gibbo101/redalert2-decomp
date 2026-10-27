// ?Rotate_Vector@Matrix3D@@QBE?AUVector3@@ABU2@@Z (0x00590CD0)
// Applies the rotation part to vector.
#include "shared/matrix3d.hpp"

Vector3 Matrix3D::Rotate_Vector(Vector3 const &vector) const
{
    return Vector3(Row[0][0] * vector.X + Row[0][1] * vector.Y + Row[0][2] * vector.Z,
                   Row[1][0] * vector.X + Row[1][1] * vector.Y + Row[1][2] * vector.Z,
                   Row[2][0] * vector.X + Row[2][1] * vector.Y + Row[2][2] * vector.Z);
}
