// HRESULT __stdcall ApplicationClass::unknown_slot3_name(BSTR *name) -- 0x00426D20
// IApplication slot: returns a new BSTR of L"Tiberian Sun" (E_POINTER without an
// out pointer).
#include "shared/application.hpp"
// @ref __imp__SysAllocString@4=0079a360
// @ref ??_C@_1BK@CPNL@?$AAT?$AAi?$AAb?$AAe?$AAr?$AAi?$AAa?$AAn?$AA?5?$AAS?$AAu?$AAn?$AA?$AA@=007cf098

HRESULT __stdcall ApplicationClass::unknown_slot3_name(BSTR *name)
{
    if (name == 0) {
        return E_POINTER;
    }
    *name = SysAllocString(L"Tiberian Sun");
    return S_OK;
}
