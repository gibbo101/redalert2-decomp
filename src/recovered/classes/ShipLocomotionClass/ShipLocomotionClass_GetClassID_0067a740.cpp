// HRESULT __stdcall ShipLocomotionClass::GetClassID(GUID *clsid) (0x0067A740)
#include "shared/ship_locomotion.hpp"
// @ref _CLSID_ShipLocomotionClass=007a1ff0

HRESULT __stdcall ShipLocomotionClass::GetClassID(GUID *clsid)
{
    if (clsid == 0) {
        return E_POINTER;
    }
    *clsid = CLSID_ShipLocomotionClass;
    return S_OK;
}
