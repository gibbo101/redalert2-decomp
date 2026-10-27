// ?Conjugate@@YI?AVQuaternion@@ABV1@@Z (0x006225F0)
// The conjugate (vector part negated).
#include "shared/quaternion.hpp"

Quaternion __fastcall Conjugate(Quaternion const &quat)
{
    return Quaternion(-quat.X, -quat.Y, -quat.Z, quat.W);
}
