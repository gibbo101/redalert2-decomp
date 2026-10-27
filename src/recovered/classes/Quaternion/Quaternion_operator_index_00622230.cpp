// ??AQuaternion@@QAEAAMH@Z (0x00622230)
// Component by index.
#include "shared/quaternion.hpp"

float &Quaternion::operator[](int index)
{
    return (&X)[index];
}
