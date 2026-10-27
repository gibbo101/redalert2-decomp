// LocomotionClass::~LocomotionClass() (0x0053CFF0)
// Forgets the linked object.
#include "shared/locomotion.hpp"
// @ref ??_7LocomotionClass@@6BIPersistStream@@@=007a33b4
// @ref ??_7LocomotionClass@@6BILocomotion@@@=007a32ec

LocomotionClass::~LocomotionClass()
{
    LinkedTo = 0;
}
