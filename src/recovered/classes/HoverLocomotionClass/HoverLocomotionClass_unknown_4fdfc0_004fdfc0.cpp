// bool HoverLocomotionClass::unknown_4fdfc0() (0x004FDFC0)
// Moving (Is_Moving as a bool test). Expanded where it is used; this
// out-of-line copy is never called.
#include "shared/hover_locomotion.hpp"

bool HoverLocomotionClass::unknown_4fdfc0()
{
    return Is_Moving() ? true : false;
}
