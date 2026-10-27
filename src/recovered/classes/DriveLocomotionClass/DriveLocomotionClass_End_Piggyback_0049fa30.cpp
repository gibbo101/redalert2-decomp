// HRESULT __stdcall DriveLocomotionClass::End_Piggyback(ILocomotion **pointer) (0x0049FA30, IPiggyback 4)
// Hands the carried locomotor (and its reference) back.
#include "shared/drive_locomotion.hpp"

HRESULT __stdcall DriveLocomotionClass::End_Piggyback(ILocomotion **pointer)
{
    if (pointer == 0) {
        return E_POINTER;
    }
    if (Piggybacker != 0) {
        *pointer = Piggybacker.Pointer;
        Piggybacker.Pointer = 0;
        return S_OK;
    }
    return S_FALSE;
}
