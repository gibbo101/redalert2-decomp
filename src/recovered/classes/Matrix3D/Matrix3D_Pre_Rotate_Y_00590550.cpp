// Matrix3D pre-multiplication by a Y rotation; original00590550.
#include "shared/matrix3d.hpp"
// @ref ?Fast_Cos@@YAMN@Z=004ba4d0
// @ref ?Fast_Sin@@YAMN@Z=004ba480
void Matrix3D::Pre_Rotate_Y(float angle)
{
    float sine = Fast_Sin(angle);
    float cosine = Fast_Cos(angle);
    float const &negative_sine = -sine;
    float first_x = Row[0][0];
    float first_y = Row[0][1];
    float first_z = Row[0][2];
    float first_translation = Row[0][3];
    float third_x = Row[2][0];
    float third_y = Row[2][1];
    float third_z = Row[2][2];
    float third_translation = Row[2][3];
    Row[0][0] = third_x * sine + first_x * cosine;
    Row[0][1] = third_y * sine + first_y * cosine;
    Row[0][2] = third_z * sine + first_z * cosine;
    Row[0][3] = third_translation * sine + first_translation * cosine;
    Row[2][0] = first_x * negative_sine + third_x * cosine;
    Row[2][1] = first_y * negative_sine + third_y * cosine;
    Row[2][2] = first_z * negative_sine + third_z * cosine;
    Row[2][3] = first_translation * negative_sine + third_translation * cosine;
}
