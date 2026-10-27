// ??0Matrix3D@@QAE@MMMMMMMMMMMM@Z (0x0058FE30)
// Matrix3D from twelve floats, row major.
#include "shared/matrix3d.hpp"

Matrix3D::Matrix3D(float m11, float m12, float m13, float m14,
                   float m21, float m22, float m23, float m24,
                   float m31, float m32, float m33, float m34)
{
    Row[0][0] = m11; Row[0][1] = m12; Row[0][2] = m13; Row[0][3] = m14;
    Row[1][0] = m21; Row[1][1] = m22; Row[1][2] = m23; Row[1][3] = m24;
    Row[2][0] = m31; Row[2][1] = m32; Row[2][2] = m33; Row[2][3] = m34;
}
