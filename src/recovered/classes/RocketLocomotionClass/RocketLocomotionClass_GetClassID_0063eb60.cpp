// HRESULT __stdcall RocketLocomotionClass::GetClassID(GUID *clsid) (0x0063EB60)
#include "shared/rocket_locomotion.hpp"
// @ref _CLSID_RocketLocomotionClass=007a2010

HRESULT __stdcall RocketLocomotionClass::GetClassID(GUID *clsid)
{
    if (clsid == 0) {
        return E_POINTER;
    }
    *clsid = CLSID_RocketLocomotionClass;
    return S_OK;
}
