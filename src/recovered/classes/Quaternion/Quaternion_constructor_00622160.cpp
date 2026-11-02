#define VECTOR3_DECLARE_WWMATH
// ??0Quaternion@@QAE@MMMM@Z (0x00622160)
// Quaternion(x, y, z, w).
#include "shared/quaternion.hpp"

Quaternion::Quaternion(float x, float y, float z, float w)
{
    X = x;
    Y = y;
    Z = z;
    W = w;
}
