// ??AQuaternion@@QBEMH@Z (0x00622240)
// Component by index (value).
#include "shared/quaternion.hpp"

float Quaternion::operator[](int index) const
{
    return (&X)[index];
}
