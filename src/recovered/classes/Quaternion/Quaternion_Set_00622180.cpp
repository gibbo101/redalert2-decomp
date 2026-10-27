// ?Set@Quaternion@@QAEXMMMM@Z (0x00622180)
// Sets the four components.
#include "shared/quaternion.hpp"

void Quaternion::Set(float x, float y, float z, float w)
{
    X = x;
    Y = y;
    Z = z;
    W = w;
}
