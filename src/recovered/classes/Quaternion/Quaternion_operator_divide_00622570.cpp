// ??K@YI?AVQuaternion@@ABV0@0@Z (0x00622570)
// a times the inverse of b.
#include "shared/quaternion.hpp"

Quaternion __fastcall operator/(Quaternion const &a, Quaternion const &b)
{
    return a * Inverse(b);
}
// @ref ??D@YI?AVQuaternion@@ABV0@0@Z=00622400
