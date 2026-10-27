// bool __stdcall TeleportLocomotionClass::Is_Piggybacking() (0x006E1BC0, IPiggyback 7)
#include "shared/teleport_locomotion.hpp"

bool __stdcall TeleportLocomotionClass::Is_Piggybacking()
{
    return Piggybacker != 0;
}
