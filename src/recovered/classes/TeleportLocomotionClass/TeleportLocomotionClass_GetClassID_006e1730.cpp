// HRESULT __stdcall TeleportLocomotionClass::GetClassID(GUID *clsid) (0x006E1730)
#include "shared/teleport_locomotion.hpp"
// @ref _CLSID_TeleportLocomotionClass=007a1fd0

HRESULT __stdcall TeleportLocomotionClass::GetClassID(GUID *clsid)
{
    if (clsid == 0) {
        return E_POINTER;
    }
    *clsid = CLSID_TeleportLocomotionClass;
    return S_OK;
}
