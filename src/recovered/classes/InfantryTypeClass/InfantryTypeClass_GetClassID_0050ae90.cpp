// HRESULT __stdcall InfantryTypeClass::GetClassID(GUID *clsid) (0x0050AE90)
#include "shared/infantry_type.hpp"
// @ref _unknown_clsid_infantry_type_7a1b10=007a1b10

HRESULT __stdcall InfantryTypeClass::GetClassID(GUID *clsid)
{
    if (clsid == 0) {
        return E_POINTER;
    }
    *clsid = unknown_clsid_infantry_type_7a1b10;
    return S_OK;
}
