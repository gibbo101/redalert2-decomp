// Matrix3D * __stdcall ShipLocomotionClass::Shadow_Matrix(Matrix3D *matrix, int *key) (0x006764C0, ILocomotion 10)
// The base shadow transform; the key is -1 (not cached) unless the unit is
// level.
#include "shared/ship_locomotion.hpp"
#include "shared/matrix3d.hpp"
// @ref ?Shadow_Matrix@LocomotionClass@@UAGPAVMatrix3D@@PAV2@PAH@Z=0053d0d0

Matrix3D * __stdcall ShipLocomotionClass::Shadow_Matrix(Matrix3D *matrix, int *key)
{
    if (!Is_Level() && key != 0) {
        *key = -1;
    }
    Matrix3D shadow;
    *matrix = *LocomotionClass::Shadow_Matrix(&shadow, key);
    return matrix;
}
