#include "shared/matrix3d.hpp"
Matrix3D __fastcall Matrix3D_Rigid_Inverse_00591420(Matrix3D const &matrix)
{
    Matrix3D inverse;
    inverse.Row[0][0] = matrix.Row[0][0]; inverse.Row[0][1] = matrix.Row[1][0]; inverse.Row[0][2] = matrix.Row[2][0];
    inverse.Row[1][0] = matrix.Row[0][1]; inverse.Row[1][1] = matrix.Row[1][1]; inverse.Row[1][2] = matrix.Row[2][1];
    inverse.Row[2][0] = matrix.Row[0][2]; inverse.Row[2][1] = matrix.Row[1][2]; inverse.Row[2][2] = matrix.Row[2][2];
    inverse.Row[0][3] = -(inverse.Row[0][0] * matrix.Row[0][3] + inverse.Row[0][1] * matrix.Row[1][3] + inverse.Row[0][2] * matrix.Row[2][3]);
    inverse.Row[1][3] = -(inverse.Row[1][0] * matrix.Row[0][3] + inverse.Row[1][1] * matrix.Row[1][3] + inverse.Row[1][2] * matrix.Row[2][3]);
    inverse.Row[2][3] = -(inverse.Row[2][0] * matrix.Row[0][3] + inverse.Row[2][1] * matrix.Row[1][3] + inverse.Row[2][2] * matrix.Row[2][3]);
    return inverse;
}
