// HRESULT __stdcall TeleportLocomotionClass::Begin_Piggyback(ILocomotion *pointer) (0x006E1960, IPiggyback 3)
// Carries the locomotor unless one is already carried.
#include "shared/teleport_locomotion.hpp"

HRESULT __stdcall TeleportLocomotionClass::Begin_Piggyback(ILocomotion *pointer)
{
    if (pointer == 0) {
        return E_POINTER;
    }
    if (Piggybacker == 0) {
        Piggybacker = pointer;
        return S_OK;
    }
    return E_FAIL;
}
