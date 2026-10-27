// HRESULT __stdcall TunnelLocomotionClass::GetClassID(GUID *clsid) (0x006F12B0)
#include "shared/tunnel_locomotion.hpp"
// @ref _CLSID_TunnelLocomotionClass=007a1f90

HRESULT __stdcall TunnelLocomotionClass::GetClassID(GUID *clsid)
{
    if (clsid == 0) {
        return E_POINTER;
    }
    *clsid = CLSID_TunnelLocomotionClass;
    return S_OK;
}
