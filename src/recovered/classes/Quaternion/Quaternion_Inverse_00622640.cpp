// ?Inverse@@YI?AVQuaternion@@ABV1@@Z (0x00622640)
// The inverse of a unit quaternion (its conjugate).
#include "shared/quaternion.hpp"

Quaternion __fastcall Inverse(Quaternion const &quat)
{
    return Quaternion(-quat[0], -quat[1], -quat[2], quat[3]);
}
