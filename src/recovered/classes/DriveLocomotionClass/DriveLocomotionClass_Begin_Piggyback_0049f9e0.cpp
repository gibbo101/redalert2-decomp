// HRESULT __stdcall DriveLocomotionClass::Begin_Piggyback(ILocomotion *pointer) (0x0049F9E0, IPiggyback 3)
// Carries the locomotor unless one is already carried.
#include "shared/drive_locomotion.hpp"

HRESULT __stdcall DriveLocomotionClass::Begin_Piggyback(ILocomotion *pointer)
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
