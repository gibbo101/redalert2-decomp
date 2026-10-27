// ??0Matrix3D@@QAE@ABV0@@Z (0x0058FE10)
// Matrix3D(Matrix3D const &matrix): member-wise copy.
#include "shared/matrix3d.hpp"

struct MatrixData { float Data[12]; };

Matrix3D::Matrix3D(Matrix3D const &matrix)
{
    *(MatrixData *)Row = *(MatrixData const *)matrix.Row;
}
