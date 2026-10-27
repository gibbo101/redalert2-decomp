// HRESULT __stdcall HoverLocomotionClass::GetClassID(GUID *clsid) (0x004FEC80)
#include "shared/hover_locomotion.hpp"
// @ref _CLSID_HoverLocomotionClass=007a1f80

HRESULT __stdcall HoverLocomotionClass::GetClassID(GUID *clsid)
{
    if (clsid == 0) {
        return E_POINTER;
    }
    *clsid = CLSID_HoverLocomotionClass;
    return S_OK;
}
