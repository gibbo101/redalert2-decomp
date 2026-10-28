// Matrix3D * __stdcall LocomotionClass::Shadow_Matrix(Matrix3D *matrix, int *key) (0x0053D0D0, ILocomotion 10)
// The shadow transform: the slope matrix of the cell's ramp turned about Z
// by the facing; a key not -1 gains the ramp (six bits) and the facing
// (five bits).
#include "shared/locomotion.hpp"
#include "shared/matrix3d.hpp"
#include "shared/cell.hpp"
// @ref ?Unknown_00718D60@@YI?AVMatrix3D@@H@Z=00718d60

Matrix3D * __stdcall LocomotionClass::Shadow_Matrix(Matrix3D *matrix, int *key)
{
    CoordStruct coord = LinkedTo->Coord;
    int ramp = Map[coord].unknown_11c;
    Matrix3D transform;
    transform = Unknown_00718D60(ramp);
    transform.Rotate_Z((float)((Dir_To_32(LinkedTo->unknown_2e0.Current()) - 8) * -0.19634954084936207));
    if (key != 0 && *key != -1) {
        *key = ((*key << 6) + ramp) << 5;
        *key |= Dir_To_32(LinkedTo->unknown_2e0.Current());
    }
    *matrix = transform;
    return matrix;
}
