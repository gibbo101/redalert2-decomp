// HRESULT __stdcall UnitTypeClass::GetClassID(GUID *clsid) (0x0070B3A0)
#include "shared/unit_type.hpp"
// @ref _unknown_clsid_unit_type_7a1b00=007a1b00

HRESULT __stdcall UnitTypeClass::GetClassID(GUID *clsid)
{
    if (clsid == 0) {
        return E_POINTER;
    }
    *clsid = unknown_clsid_unit_type_7a1b00;
    return S_OK;
}
