// ?Scale@Quaternion@@QAEXM@Z (0x00622200)
// Multiplies the components by scale.
#include "shared/quaternion.hpp"

void Quaternion::Scale(float scale)
{
    X = scale * X;
    Y = scale * Y;
    Z = scale * Z;
    W = scale * W;
}
