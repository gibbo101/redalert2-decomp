// ??4Quaternion@@QAE?AV0@ABV0@@Z (0x00622250)
// Assignment, returning a copy.
#include "shared/quaternion.hpp"

Quaternion Quaternion::operator=(Quaternion const &quat)
{
    X = quat[0];
    Y = quat[1];
    Z = quat[2];
    W = quat[3];
    return *this;
}
