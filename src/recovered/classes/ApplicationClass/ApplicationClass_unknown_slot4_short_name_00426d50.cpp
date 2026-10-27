// HRESULT __stdcall ApplicationClass::unknown_slot4_short_name(BSTR *name) -- 0x00426D50
// IApplication slot: returns a new BSTR of L"Sun" (E_POINTER without an
// out pointer).
#include "shared/application.hpp"
// @ref __imp__SysAllocString@4=0079a360
// @ref ??_C@_17KLCK@?$AAS?$AAu?$AAn?$AA?$AA@=007cf0b4

HRESULT __stdcall ApplicationClass::unknown_slot4_short_name(BSTR *name)
{
    if (name == 0) {
        return E_POINTER;
    }
    *name = SysAllocString(L"Sun");
    return S_OK;
}
