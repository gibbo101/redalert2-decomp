// HRESULT __stdcall BuildingLightClass::GetClassID(GUID *clsid) (0x004340A0)
#include "shared/building_light.hpp"
// @ref _CLSID_BuildingLightClass=007a1ca0

HRESULT __stdcall BuildingLightClass::GetClassID(GUID *clsid)
{
    if (clsid == 0) {
        return E_POINTER;
    }
    *clsid = CLSID_BuildingLightClass;
    return S_OK;
}
