// ?Normalize@Quaternion@@QAEXXZ (0x006221A0)
// Divides the components by the squared length (nothing for a zero quaternion).
#include "shared/quaternion.hpp"
// @ref __real@4@00000000000000000000=0079a738

void Quaternion::Normalize()
{
    float len2 = X * X + Y * Y + Z * Z + W * W;
    if (0.0f != len2) {
        X /= len2;
        Y /= len2;
        Z /= len2;
        W /= len2;
    }
}
