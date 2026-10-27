// ??0Matrix3D@@QAE@ABUVector3@@000@Z (0x0058FE90)
// Matrix3D from three row vectors and a translation.
#include "shared/matrix3d.hpp"

Matrix3D::Matrix3D(Vector3 const &x, Vector3 const &y, Vector3 const &z, Vector3 const &position)
{
    Row[0][0] = x.X; Row[0][1] = x.Y; Row[0][2] = x.Z; Row[0][3] = position.X;
    Row[1][0] = y.X; Row[1][1] = y.Y; Row[1][2] = y.Z; Row[1][3] = position.Y;
    Row[2][0] = z.X; Row[2][1] = z.Y; Row[2][2] = z.Z; Row[2][3] = position.Z;
}
