// HRESULT __stdcall DropPodLocomotionClass::End_Piggyback(ILocomotion **pointer) (0x004A6380, IPiggyback 4)
// Hands the carried locomotor (and its reference) back.
#include "shared/droppod_locomotion.hpp"

HRESULT __stdcall DropPodLocomotionClass::End_Piggyback(ILocomotion **pointer)
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
