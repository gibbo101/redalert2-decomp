// HRESULT __stdcall OverlayTypeClass::GetClassID(GUID *clsid) (0x005DCF30)
#include "shared/overlay_type.hpp"
// @ref _CLSID_OverlayTypeClass=007a1b70

HRESULT __stdcall OverlayTypeClass::GetClassID(GUID *clsid)
{
    if (clsid == 0) {
        return E_POINTER;
    }
    *clsid = CLSID_OverlayTypeClass;
    return S_OK;
}
