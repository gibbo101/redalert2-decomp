// HRESULT __stdcall JumpjetLocomotionClass::GetClassID(GUID *clsid) (0x0052FBA0)
#include "shared/jumpjet_locomotion.hpp"
// @ref _CLSID_JumpjetLocomotionClass=007a2000

HRESULT __stdcall JumpjetLocomotionClass::GetClassID(GUID *clsid)
{
    if (clsid == 0) {
        return E_POINTER;
    }
    *clsid = CLSID_JumpjetLocomotionClass;
    return S_OK;
}
