// HRESULT __stdcall LocomotionClass::GetSizeMax(ULARGE_INTEGER *size) (0x0053D440)
// Size() plus the saved address.
#include "shared/locomotion.hpp"

HRESULT __stdcall LocomotionClass::GetSizeMax(ULARGE_INTEGER *size)
{
    if (size == 0) {
        return E_POINTER;
    }
    size->QuadPart = (unsigned)(Size() + sizeof(LocomotionClass *));
    return S_OK;
}
