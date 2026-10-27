// HRESULT __stdcall BuildingTypeClass::GetClassID(GUID *clsid) (0x0045E0A0)
#include "shared/building_type.hpp"
// @ref _unknown_clsid_building_type_7a1b30=007a1b30

HRESULT __stdcall BuildingTypeClass::GetClassID(GUID *clsid)
{
    if (clsid == 0) {
        return E_POINTER;
    }
    *clsid = unknown_clsid_building_type_7a1b30;
    return S_OK;
}
