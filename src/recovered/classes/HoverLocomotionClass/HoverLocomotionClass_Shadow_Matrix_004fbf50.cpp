// Matrix3D * __stdcall HoverLocomotionClass::Shadow_Matrix(Matrix3D *matrix, int *key) (0x004FBF50, ILocomotion 10)
// The base shadow transform; while the hull is tilted (either angle at
// +0x280/+0x284 at least 0.005) the key is -1 (not cached).
#include "shared/hover_locomotion.hpp"
#include "shared/matrix3d.hpp"
#include "shared/crt_math.hpp"
// @ref __real@8@3ff7a3d70a3d70a3d800=0079d170
// @ref ?Shadow_Matrix@LocomotionClass@@UAGPAVMatrix3D@@PAV2@PAH@Z=0053d0d0

Matrix3D * __stdcall HoverLocomotionClass::Shadow_Matrix(Matrix3D *matrix, int *key)
{
    if ((fabs(LinkedTo->unknown_280) >= 0.005 || fabs(LinkedTo->unknown_284) >= 0.005) && key != 0) {
        *key = -1;
    }
    Matrix3D shadow;
    *matrix = *LocomotionClass::Shadow_Matrix(&shadow, key);
    return matrix;
}
