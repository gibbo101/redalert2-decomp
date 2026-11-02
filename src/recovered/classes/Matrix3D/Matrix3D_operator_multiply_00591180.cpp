// Matrix3D operator*(Matrix3D const &, Matrix3D const &) (0x00591180): the product of two transforms
// (Westwood's wwmath matrix product). Left's 3x3 and all of right are read into float locals first; the
// result is a local returned through the copy constructor, which this unit defines first (0x0058FE10) and
// expands here.
#include "shared/matrix3d.hpp"

Matrix3D __fastcall operator*(Matrix3D const &left, Matrix3D const &right)
{
    Matrix3D result;
    float a00 = left.Row[0][0];
    float a01 = left.Row[0][1];
    float a02 = left.Row[0][2];
    float a10 = left.Row[1][0];
    float a11 = left.Row[1][1];
    float a12 = left.Row[1][2];
    float a20 = left.Row[2][0];
    float a21 = left.Row[2][1];
    float a22 = left.Row[2][2];
    float b00 = right.Row[0][0];
    float b01 = right.Row[0][1];
    float b02 = right.Row[0][2];
    float b03 = right.Row[0][3];
    float b10 = right.Row[1][0];
    float b11 = right.Row[1][1];
    float b12 = right.Row[1][2];
    float b13 = right.Row[1][3];
    float b20 = right.Row[2][0];
    float b21 = right.Row[2][1];
    float b22 = right.Row[2][2];
    float b23 = right.Row[2][3];
    result.Row[0][0] = a00 * b00 + a01 * b10 + a02 * b20;
    result.Row[1][0] = a10 * b00 + a11 * b10 + a12 * b20;
    result.Row[2][0] = a20 * b00 + a21 * b10 + a22 * b20;
    result.Row[0][1] = a00 * b01 + a01 * b11 + a02 * b21;
    result.Row[1][1] = a10 * b01 + a11 * b11 + a12 * b21;
    result.Row[2][1] = a20 * b01 + a21 * b11 + a22 * b21;
    result.Row[0][2] = a00 * b02 + a01 * b12 + a02 * b22;
    result.Row[1][2] = a10 * b02 + a11 * b12 + a12 * b22;
    result.Row[2][2] = a20 * b02 + a21 * b12 + a22 * b22;
    result.Row[0][3] = a00 * b03 + a01 * b13 + a02 * b23 + left.Row[0][3];
    result.Row[1][3] = a10 * b03 + a11 * b13 + a12 * b23 + left.Row[1][3];
    result.Row[2][3] = a20 * b03 + a21 * b13 + a22 * b23 + left.Row[2][3];
    return result;
}
