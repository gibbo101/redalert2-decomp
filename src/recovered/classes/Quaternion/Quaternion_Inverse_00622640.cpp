// ?Inverse@@YI?AVQuaternion@@ABV1@@Z (0x00622640)
// The inverse of a unit quaternion (its conjugate).
#include "shared/quaternion.hpp"

Quaternion __fastcall Inverse(Quaternion const &quat)
{
    return Quaternion(-quat.X, -quat.Y, -quat.Z, quat.W);
}
