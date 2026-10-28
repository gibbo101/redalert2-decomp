// Matrix3D * __stdcall FlyLocomotionClass::Shadow_Matrix(Matrix3D *matrix, int *key) (0x004BF280, ILocomotion 10)
// As LocomotionClass::Shadow_Matrix, turned by the second facing (+0x2F8);
// a dropship's shadow ignores the cell's ramp.
#include "shared/fly_locomotion.hpp"
#include "shared/matrix3d.hpp"
#include "shared/cell.hpp"
// @ref ?Unknown_00718D60@@YI?AVMatrix3D@@H@Z=00718d60

Matrix3D * __stdcall FlyLocomotionClass::Shadow_Matrix(Matrix3D *matrix, int *key)
{
    CoordStruct coord = LinkedTo->Coord;
    int ramp = Map[coord].unknown_11c;
    if (LinkedTo->unknown_slot32()->IsDropship) {
        ramp = 0;
    }
    Matrix3D transform;
    transform = Unknown_00718D60(ramp);
    transform.Rotate_Z((float)((Dir_To_32(LinkedTo->unknown_2f8.Current()) - 8) * -0.19634954084936207));
    if (key != 0 && *key != -1) {
        *key = ((*key << 6) + ramp) << 5;
        *key |= Dir_To_32(LinkedTo->unknown_2f8.Current());
    }
    *matrix = transform;
    return matrix;
}
