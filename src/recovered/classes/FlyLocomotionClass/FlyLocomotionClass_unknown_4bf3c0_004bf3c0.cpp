// bool FlyLocomotionClass::unknown_4bf3c0() (0x004BF3C0)
// Not +0x51, and either not +0x50 or at least half the +0x38 height up
// (slot 108). Expanded where it is used; this out-of-line copy is never
// called.
#include "shared/fly_locomotion.hpp"

bool FlyLocomotionClass::unknown_4bf3c0()
{
    if (!unknown_51 && (!unknown_50 || LinkedTo->unknown_slot108() >= unknown_38 / 2)) {
        return true;
    }
    return false;
}
