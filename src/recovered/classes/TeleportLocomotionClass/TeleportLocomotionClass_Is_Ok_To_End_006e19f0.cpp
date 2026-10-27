// bool __stdcall TeleportLocomotionClass::Is_Ok_To_End() (0x006E19F0, IPiggyback 5)
// Once idle (no warp under way) while carrying a locomotor.
#include "shared/teleport_locomotion.hpp"

bool __stdcall TeleportLocomotionClass::Is_Ok_To_End()
{
    if (!Is_Moving() && Piggybacker != 0 && !unknown_35 && !LinkedTo->unknown_210 && !unknown_38) {
        return true;
    }
    return false;
}
