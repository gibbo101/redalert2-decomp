// Converts a quaternion rotation to an affine matrix with zero translation.
#include "shared/quaternion.hpp"

Matrix3D __fastcall Build_Matrix3D(Quaternion const &rotation)
{
    Matrix3D matrix;
    matrix.Row[0][0] = 1.0f - 2.0f * (rotation[1] * rotation[1] + rotation[2] * rotation[2]);
    matrix.Row[0][1] = 2.0f * (rotation[0] * rotation[1] - rotation[2] * rotation[3]);
    matrix.Row[0][2] = 2.0f * (rotation[2] * rotation[0] + rotation[1] * rotation[3]);
    matrix.Row[1][0] = 2.0f * (rotation[0] * rotation[1] + rotation[2] * rotation[3]);
    matrix.Row[1][1] = 1.0f - 2.0f * (rotation[2] * rotation[2] + rotation[0] * rotation[0]);
    matrix.Row[1][2] = 2.0f * (rotation[1] * rotation[2] - rotation[0] * rotation[3]);
    matrix.Row[2][0] = 2.0f * (rotation[2] * rotation[0] - rotation[1] * rotation[3]);
    matrix.Row[2][1] = 2.0f * (rotation[1] * rotation[2] + rotation[0] * rotation[3]);
    matrix.Row[2][2] = 1.0f - 2.0f * (rotation[1] * rotation[1] + rotation[0] * rotation[0]);
    matrix.Row[0][3] = matrix.Row[1][3] = matrix.Row[2][3] = 0.0f;
    return matrix;
}
