// bool TeleportLocomotionClass::unknown_slot11() (0x006DFD30, IPersistStream-side slot 11)
// Not moving.
#include "shared/teleport_locomotion.hpp"

bool TeleportLocomotionClass::unknown_slot11()
{
    return Is_Moving() ? false : true;
}
