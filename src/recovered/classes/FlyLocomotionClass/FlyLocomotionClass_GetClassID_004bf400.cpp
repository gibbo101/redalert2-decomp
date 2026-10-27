// HRESULT __stdcall FlyLocomotionClass::GetClassID(GUID *clsid) (0x004BF400)
#include "shared/fly_locomotion.hpp"
// @ref _CLSID_FlyLocomotionClass=007a1fc0

HRESULT __stdcall FlyLocomotionClass::GetClassID(GUID *clsid)
{
    if (clsid == 0) {
        return E_POINTER;
    }
    *clsid = CLSID_FlyLocomotionClass;
    return S_OK;
}
