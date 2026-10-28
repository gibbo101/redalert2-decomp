// Matrix3D * __stdcall LocomotionClass::Draw_Matrix(Matrix3D *matrix, int *key) (0x0053D030, ILocomotion 9)
// The body transform: the facing as one of 32 directions turned about Z;
// a key not -1 gains the facing as five more bits.
#include "shared/locomotion.hpp"
#include "shared/matrix3d.hpp"
// @ref __real@8@bffcc90fdaa22168c000=0079d090
// @ref ?Make_Identity@Matrix3D@@=00590060
// @ref ?Rotate_Z@Matrix3D@@=005909a0
// @ref ?Current@FacingClass@@=004b8be0

Matrix3D * __stdcall LocomotionClass::Draw_Matrix(Matrix3D *matrix, int *key)
{
    Matrix3D transform;
    transform.Make_Identity();
    transform.Rotate_Z((float)((Dir_To_32(LinkedTo->unknown_2e0.Current()) - 8) * -0.19634954084936207));
    if (key != 0 && *key != -1) {
        *key <<= 5;
        *key |= Dir_To_32(LinkedTo->unknown_2e0.Current());
    }
    *matrix = transform;
    return matrix;
}
