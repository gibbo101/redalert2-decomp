// HRESULT __stdcall MechLocomotionClass::GetClassID(GUID *clsid) (0x00593120)
#include "shared/mech_locomotion.hpp"
// @ref _CLSID_MechLocomotionClass=007a1fe0

HRESULT __stdcall MechLocomotionClass::GetClassID(GUID *clsid)
{
    if (clsid == 0) {
        return E_POINTER;
    }
    *clsid = CLSID_MechLocomotionClass;
    return S_OK;
}
