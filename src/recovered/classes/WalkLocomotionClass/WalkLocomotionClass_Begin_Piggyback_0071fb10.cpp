// HRESULT __stdcall WalkLocomotionClass::Begin_Piggyback(ILocomotion *pointer) (0x0071FB10, IPiggyback 3)
// Carries the locomotor unless one is already carried.
#include "shared/walk_locomotion.hpp"

HRESULT __stdcall WalkLocomotionClass::Begin_Piggyback(ILocomotion *pointer)
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
