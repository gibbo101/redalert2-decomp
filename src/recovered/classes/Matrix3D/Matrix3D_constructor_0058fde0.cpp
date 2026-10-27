// ??0Matrix3D@@QAE@PBM@Z (0x0058FDE0)
// Matrix3D(float const *matrix): copies twelve floats, row by row.
#include "shared/matrix3d.hpp"

Matrix3D::Matrix3D(float const *matrix)
{
    float *dest = &Row[0][0];
    for (int index = 0; index < 12; index++) {
        dest[index] = matrix[index];
    }
}
