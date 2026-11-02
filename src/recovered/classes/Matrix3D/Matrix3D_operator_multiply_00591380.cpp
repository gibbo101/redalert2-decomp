// ??D@YI?AUVector3@@ABVMatrix3D@@ABU0@@Z (0x00591380)
// Transforms a point: the rotation rows applied to vector, plus the translation column.
// The rotation elements are read into one-use float locals first; that fixes the x87
// operand order and the scheduling of the return-pointer copy (mov eax, ecx).
#include "shared/matrix3d.hpp"

Vector3 __fastcall operator*(Matrix3D const &matrix, Vector3 const &vector)
{
    float m00 = matrix.Row[0][0], m01 = matrix.Row[0][1], m02 = matrix.Row[0][2];
    float m10 = matrix.Row[1][0], m11 = matrix.Row[1][1], m12 = matrix.Row[1][2];
    float m20 = matrix.Row[2][0], m21 = matrix.Row[2][1], m22 = matrix.Row[2][2];
    return Vector3(m00 * vector.X + m01 * vector.Y + m02 * vector.Z + matrix.Row[0][3],
                   (m10 * vector.X) + m11 * vector.Y + m12 * vector.Z + matrix.Row[1][3],
                   (m20 * vector.X) + m21 * vector.Y + m22 * vector.Z + matrix.Row[2][3]);
}
